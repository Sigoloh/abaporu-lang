//
// Created by augusto.sigolo on 06/07/24.
//

#include "Compiled_Block.cpp"
using namespace std;

class Compiler {
    private:
            int slots_needed = 1;
            int virtual_cursor = 0;
            Interpreter_Graph* graph_to_run = nullptr;
            bool waiting_block_closing = false;
            vector<Compiled_Block*> blocks;
            string out_file = "./outputs/output.cpp";
            string out_dir = "outputs";
            string blocks_buff = "";
            string cpp_func_buff = "";
            string cpp_buff = "";
    public:
        [[nodiscard]] Compiler(Interpreter_Graph* graph, const string &out_file = "./outputs/output.cpp", const string &out_dir = "outputs") {
            this->out_dir = out_dir;
            this->out_file = out_file;
            this->graph_to_run = graph;
        }

        ~Compiler() {
            delete this;
        }

        void create_cpp_file(const string &content) const {
            ofstream out_file_created(this->out_file);
            out_file_created << content <<endl;
            out_file_created.close();
         }

        void handle_simple_operations(string operation) {
            if(operation == "add") {
                this->cpp_buff += "++sausage[curr_sausage_index];\n";
            }

            if(operation == "sub") {
                this->cpp_buff += "--sausage[curr_sausage_index];\n";
            }

            if(operation == "next") {
                if(this->virtual_cursor + 1 >= this->slots_needed) {
                    ++this->slots_needed;
                }
                ++this->virtual_cursor;
                this->cpp_buff += "++curr_sausage_index;\n";
            }

            if(operation == "prev") {
                if(this->virtual_cursor - 1 < 0) {
                    cout<<"[INTERPRETATION ERROR] You tried to put the curser outside the scope of the sausage"<<endl;
                } else {
                    --this->virtual_cursor;
                    this->cpp_buff += "--curr_sausage_index;\n";
                }
            }

            if(operation == "puts") {
                this->cpp_buff += "cout<<char(sausage[curr_sausage_index]);\n";
            }

            if(operation == "putv") {
                this->cpp_buff += "cout<<sausage[curr_sausage_index];\n";
            }
        }

        long find_block_by_name(const string& block_name) {
            for(unsigned long curr_block_idx = 0; curr_block_idx < this->blocks.size(); curr_block_idx++) {
                if(this->blocks.at(curr_block_idx)->get_name() == block_name) {
                    return curr_block_idx;
                }
            }

            return -1;
        }

        void handle_block_execution(string block_name, Interpreter_Graph_Node* curr_instruction, bool can_create) {
            long block_idx = this->find_block_by_name(block_name);
            if(block_idx != -1) {
                this->cpp_buff += block_name + "(sausage, &curr_sausage_index);\n";
            }else {
                if(can_create) {
                    auto new_block = new Compiled_Block(block_name);
                    this->blocks.push_back(new_block);
                    this->waiting_block_closing = true;
                } else {
                    cout<<"[CODE ERROR] You cannot create blocks inside loops or inside other blocks"<<endl;
                }

            }
        }

        void handle_loop_execution(int count, Interpreter_Graph_Node* curr_instruction) {
                Interpreter_Graph_Node* loop_next_instruction = curr_instruction->get_next();
                while(loop_next_instruction->get_operation() != "endl") {
                    this->cpp_buff += "for(int i = 0; i < " + to_string(count) + "; i++){\n";

                    string loop_operation = loop_next_instruction->get_operation();

                    if(loop_operation == "defb") {
                        string block_name = loop_next_instruction->get_instruction().replace(0, 1, "b");
                        this->handle_block_execution(block_name, loop_next_instruction, false);
                    }

                    this->handle_simple_operations(loop_operation);

                    loop_next_instruction = loop_next_instruction->get_next();
                }
                this->cpp_buff += "}\n";
        }

        int handle_block_creation(Interpreter_Graph_Node* curr_instruction) {
            int offset = 0;

            string operation = curr_instruction->get_operation();

            long last_block_idx = this->blocks.size() - 1;

            if(last_block_idx == -1) {
                cout<<"[RUNNER ERROR] Something went wrong. The Runner tried to add an instruction in the block when there is none declared"<<endl;
                return -1;
            }

            offset = this->blocks.at(last_block_idx)->handle_instruction(curr_instruction);

            if(operation == "endb") {
                this->blocks_buff += this->blocks[last_block_idx]->get_full_block();
                this->waiting_block_closing = false;
            }

            return offset;
        }


        void compile() {
            Interpreter_Graph_Node* curr_instruction = this->graph_to_run->get_root();
            while(curr_instruction != nullptr) {
                string operation = curr_instruction->get_operation();

                if(this->waiting_block_closing) {
                    int block_offset = this->handle_block_creation(curr_instruction);
                    if(block_offset > 0) {
                        for(int i = 0; i < block_offset; i++) {
                            curr_instruction = curr_instruction->get_next();
                        }
                    }
                    curr_instruction = curr_instruction->get_next();

                    continue;
                }

                if(operation != "defb" && operation != "defl" && !waiting_block_closing) {
                    this->handle_simple_operations(operation);
                }

                if(operation == "defb") {
                    string block_name = curr_instruction->get_instruction().replace(0, 1, "b");
                    this->handle_block_execution(block_name, curr_instruction, true);
                }

                if(operation == "defl") {
                    int count = curr_instruction->get_aux();
                    this->handle_loop_execution(count, curr_instruction);
                }

                curr_instruction = curr_instruction->get_next();
            }
            string cpp_header = "#include <iostream>\n"
                                "using namespace std;\n"
                                + this->blocks_buff +
                                "int main(){\n"
                                "int *sausage;\n"
                                "int curr_sausage_index = 0;\n"
                                "sausage = new int[10000];\n";
            cpp_header += this->cpp_buff;
            cpp_header += "cout<<char(10);";
            cpp_header += "return 0;\n}";
            this->create_cpp_file(cpp_header);
        }
};
