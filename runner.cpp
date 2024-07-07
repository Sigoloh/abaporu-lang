#include <iostream>
#include<vector>
#include <pstl/algorithm_fwd.h>

#include "Block.cpp"
using namespace std;
class Runner{
    private:
        int slots_needed;
        Interpreter_Graph* graph_to_run = nullptr;
        int* sausage;
        bool waiting_block_closing = false;
        vector<Block*> blocks;
        int curr_sausage_index = 0;

    public:
        Runner(Interpreter_Graph* graph_to_run){
            this->slots_needed = 1;
            this->sausage = new int[1];
            this->graph_to_run = graph_to_run;
            for(int i = 0; i < 1; i++){
               this->sausage[i] = 0;
            }

        }

        ~Runner(){
            delete this;
        }

        void handle_simple_operations(string operation) {
            if(operation == "add") {
                //cout<<"Curr value "<<this->sausage[this->curr_sausage_index]<<" goes to "<<this->sausage[this->curr_sausage_index] + 1<<endl;
                ++this->sausage[this->curr_sausage_index];
            }

            if(operation == "sub") {
                --this->sausage[this->curr_sausage_index];
            }

            if(operation == "next") {
                if(this->curr_sausage_index + 1 >= this->slots_needed) {
                    this->add_slot_to_sausage();
                }
                ++this->curr_sausage_index;
            }

            if(operation == "prev") {
                if(this->curr_sausage_index - 1 < 0) {
                    cout<<"[INTERPRETATION ERROR] You tried to put the curser outside the scope of the sausage"<<endl;
                } else {
                    --this->curr_sausage_index;
                }
            }

            if(operation == "puts") {
                cout<<char(this->sausage[this->curr_sausage_index]);
            }

            if(operation == "putv") {
                cout<<this->sausage[this->curr_sausage_index];
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

        void print_sausage() {
            for(int i = 0; i < this->slots_needed; i++) {
                cout<<this->sausage[i]<<" ";
            }
        }

        void add_slot_to_sausage() {
            ++this->slots_needed;
            int* new_sausage = new int[this->slots_needed];
            for(int i = 0; i < this->slots_needed; i++) {
                if(i < this->slots_needed - 1) {
                    int value_to_move = this->sausage[i];
                    new_sausage[i] = value_to_move;
                }else {
                    new_sausage[i] = 0;
                }
            }
            this->sausage = new_sausage;
        }

        void print_all_blocks() {
            for(auto & block : this->blocks) {
                cout<<block->get_name()<<endl;
            }
            cout<<endl;
        }

        void handle_loop_execution(int count, Interpreter_Graph_Node* curr_instruction) {
            while(count != 1) {
                --count;
                Interpreter_Graph_Node* loop_next_instruction = curr_instruction->get_next();
                while(loop_next_instruction->get_operation() != "endl") {
                    string loop_operation = loop_next_instruction->get_operation();

                    if(loop_operation == "defb") {
                        this->handle_block_execution(loop_next_instruction, false);
                    }

                    this->handle_simple_operations(loop_operation);

                    loop_next_instruction = loop_next_instruction->get_next();
                }

            }
        }

        void handle_block_execution(Interpreter_Graph_Node* curr_instruction, bool can_create) {
            long block_idx = this->find_block_by_name(curr_instruction->get_instruction());
            if(block_idx != -1) {
                this->run_block(block_idx);
            }else {
                if(can_create) {
                    auto new_block = new Block(curr_instruction->get_instruction());
                    this->blocks.push_back(new_block);
                    this->waiting_block_closing = true;
                } else {
                    cout<<"[CODE ERROR] You cannot create blocks inside loops or inside other blocks"<<endl;
                }

            }
        }

        void handle_block_creation(Interpreter_Graph_Node* curr_instruction) {
            string operation = curr_instruction->get_operation();

            long last_block_idx = this->blocks.size() - 1;

            if(last_block_idx == -1) {
                cout<<"[RUNNER ERROR] Something went wrong. The Runner tried to add an instruction in the block when there is none declared"<<endl;
                return;
            }

            this->blocks.at(last_block_idx)->handle_instruction(curr_instruction->get_instruction());

            if(operation == "endb") {
                this->waiting_block_closing = false;
            }

        }

        void run_block(long block_idx) {
            if(block_idx >= this->blocks.size() || block_idx < 0) {
                cout<<"[RUNNER ERROR] Runner tried to run a block that is outside the scope of defined blocks"<<endl;
                return;
            }
            Block* block_to_run = this->blocks.at(block_idx);

            Interpreter_Graph_Node* curr_instruction = block_to_run->get_root();

            while(curr_instruction != nullptr) {
                string operation = curr_instruction->get_operation();

                if(operation != "defl" && operation != "defb") {
                    this->handle_simple_operations(operation);
                }

                if(operation == "defl") {
                    int count = curr_instruction->get_aux();
                    this->handle_loop_execution(count, curr_instruction);
                }


                if(operation == "defb") {
                    this->handle_block_execution(curr_instruction, false);
                }

                curr_instruction = curr_instruction->get_next();
            }
        }

        void run(){
            Interpreter_Graph_Node* curr_instruction = this->graph_to_run->get_root();

            while(curr_instruction != nullptr) {
                string operation = curr_instruction->get_operation();

                if(this->waiting_block_closing) {
                    this->handle_block_creation(curr_instruction);

                    curr_instruction = curr_instruction->get_next();

                    continue;
                }

                if(operation != "defl" && operation != "defb" && !this->waiting_block_closing) {
                    this->handle_simple_operations(operation);

                    curr_instruction = curr_instruction->get_next();

                    continue;
                }

                if(operation == "defb") {
                    this->handle_block_execution(curr_instruction, true);
                }

                if(operation == "defl") {
                    int count = curr_instruction->get_aux();
                    this->handle_loop_execution(count, curr_instruction);
                }

                curr_instruction = curr_instruction->get_next();
            }

            cout<<char(10);
        }

};