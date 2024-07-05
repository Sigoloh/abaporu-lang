#include <iostream>

class Runner{
    private:
        int slots_needed;
        Interpreter_Graph* graph_to_run = nullptr;
        int* sausage;
        int curr_sausage_index = 0;

    public:
        Runner(Interpreter_Graph* graph_to_run){
            this->slots_needed = graph_to_run->get_slots_needed();
            cout<<"Slots"<<endl;
            cout<<this->slots_needed<<endl;
            this->sausage = new int[this->slots_needed];
            this->graph_to_run = graph_to_run;

            for(int i = 0; i < this->slots_needed; i++){
               this->sausage[i] = 0;
            }

        }

        ~Runner(){
            delete this;
        }

        void handle_simple_operations(string operation) {
            if(operation == "add") {
                ++this->sausage[this->curr_sausage_index];
            }

            if(operation == "sub") {
                --this->sausage[this->curr_sausage_index];
            }

            if(operation == "next") {
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

        void run(){
            Interpreter_Graph_Node* curr_instruction = this->graph_to_run->get_root();

            while(curr_instruction->get_next() != nullptr) {
                string operation = curr_instruction->get_operation();

                if(operation != "defl") {
                    this->handle_simple_operations(operation);
                }

                if(operation == "defl") {
                    int count = curr_instruction->get_aux();
                    while(count != 1) {
                        --count;
                        Interpreter_Graph_Node* loop_next_instruction = curr_instruction->get_next();
                        while(loop_next_instruction->get_operation() != "endl") {
                            string loop_operation = loop_next_instruction->get_operation();

                            this->handle_simple_operations(loop_operation);

                            loop_next_instruction = loop_next_instruction->get_next();
                        }

                    }
                }

                curr_instruction = curr_instruction->get_next();
            }
        }

};