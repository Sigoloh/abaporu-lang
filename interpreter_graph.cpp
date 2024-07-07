//
// Created by augusto.sigolo on 03/07/24.
//

#include <iostream>
#include <numeric>

#include "./interpreter_graph_node.cpp"
#include <utility>
#include <vector>
using namespace std;

class Interpreter_Graph{
    private:
        Interpreter_Graph_Node* instructions_root = nullptr;
        string name;
        string run_status;
        int slots_needed = 1;
        bool waiting_loop = false;
        bool waiting_block = false;
        Interpreter_Graph* loop_to_run = nullptr;
        vector<Interpreter_Graph*> blocks;
        [[nodiscard]] Interpreter_Graph_Node* get_last_instruction() const {
            Interpreter_Graph_Node* curr = this->instructions_root;

            while (curr->get_next() != nullptr) {
                curr = curr->get_next();
            }

            return curr;
        }

    public:
        explicit Interpreter_Graph(){
            this->run_status = "Interpreting";
        }

        ~Interpreter_Graph(){
            delete this;
        }

        void add_instruction(string instruction, string operation){
            if(this->instructions_root == nullptr){
                this->instructions_root = new Interpreter_Graph_Node(instruction, operation);
            }

            return;
        }

        Interpreter_Graph_Node* get_root(){
            return this->instructions_root;
        }

        void see_last_node() {
            auto node = this->get_root();
            while(node->get_next() != nullptr) {
                node = node->get_next();
            }
            node->see_resume();
        }

        void handle_instruction(const string& instruction) {
            Interpreter_Graph_Node* new_instruction = nullptr;
            if(instruction == "#FF0000"){
                new_instruction = new Interpreter_Graph_Node(instruction, "add");
            } else if (instruction == "#0000FF"){
                new_instruction = new Interpreter_Graph_Node(instruction, "sub");
            } else if (instruction == "#00FF00"){
                ++this->slots_needed;
                new_instruction = new Interpreter_Graph_Node(instruction, "next");
            } else if (instruction == "#FFF800"){
                new_instruction = new Interpreter_Graph_Node(instruction, "prev");
            } else if (instruction == "#FFFFFF"){
                new_instruction = new Interpreter_Graph_Node(instruction, "puts");
            } else if (instruction == "#555555"){
                new_instruction = new Interpreter_Graph_Node(instruction, "putv");
            } else if (instruction == "#FFA500"){
                new_instruction = new Interpreter_Graph_Node(instruction, "endb");
            } else if (instruction == "#3FFFE8"){
                new_instruction = new Interpreter_Graph_Node(instruction, "endl");
            }  else if (instruction.substr(0, 3) == "#11"){
                stringstream loop_count_hex;

                loop_count_hex << hex << instruction.substr(3, 6);

                int loop_count;

                loop_count_hex >> loop_count;

                new_instruction = new Interpreter_Graph_Node(instruction, "defl", loop_count);
            } else {
                new_instruction = new Interpreter_Graph_Node(instruction, "defb");
            }

            if(this->instructions_root == nullptr) {
                this->instructions_root = new_instruction;

                return;
            }

            Interpreter_Graph_Node* last_instruction = this->get_last_instruction();

            last_instruction->set_next(new_instruction);
        }

        void print_graph() const {
            Interpreter_Graph_Node* curr = this->instructions_root;

            while(curr->get_next() != nullptr){
                curr->see_resume();
                curr = curr->get_next();
            }
        }

        [[nodiscard]] int get_slots_needed() const {
            return this->slots_needed;
        }
};