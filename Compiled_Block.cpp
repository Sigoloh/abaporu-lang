class Compiled_Block{
    private:
        string name;
        string cpp_buff;
    public:
        [[nodiscard]] explicit Compiled_Block(const string &name) {
            this->name = name;
        }

        ~Compiled_Block() {
            delete this;
        }

        int handle_instruction(Interpreter_Graph_Node* node) {
            int offset = 0;
            string operation = node->get_operation();
            if(operation == "add") {
                this->cpp_buff += "++sausage[*curr_sausage_index];\n";
            }

            if(operation == "sub") {
                this->cpp_buff += "--sausage[*curr_sausage_index];\n";
            }

            if(operation == "next") {
                this->cpp_buff += "++*curr_sausage_index;\n";
            }

            if(operation == "prev") {
                if(1 < 0) {
                    cout<<"[INTERPRETATION ERROR] You tried to put the curser outside the scope of the sausage"<<endl;
                } else {
                    this->cpp_buff += "--*curr_sausage_index;\n";
                }
            }

            if(operation == "puts") {
                this->cpp_buff += "cout<<char(sausage[*curr_sausage_index]);\n";
            }

            if(operation == "putv") {
                this->cpp_buff += "cout<<sausage[*curr_sausage_index];\n";
            }

            if(operation == "defb") {
                string block_name = node->get_instruction().replace(0,1, "b");
                this->cpp_buff += block_name + "(sausage, curr_sausage_index);\n";
            }

            if(operation == "defl") {
                Interpreter_Graph_Node* curr_instruction = node->get_next();
                long count = node->get_aux();
                this->cpp_buff += "for(int i = 0; i < " + to_string(count) + "; i++){\n";
                while(curr_instruction != nullptr && curr_instruction->get_operation() != "endl") {
                    ++offset;
                    this->handle_instruction(curr_instruction);
                    curr_instruction = curr_instruction->get_next();
                }
                this->cpp_buff += "}\n";
            }
            return offset;
        }

        string get_name() {
            return this->name;
        }

        string get_full_block() {
            string block_content = "void " + this->name + "(int* sausage, int* curr_sausage_index){\n";
            block_content += this->cpp_buff;
            block_content += "}\n";
            return block_content;
        }
};