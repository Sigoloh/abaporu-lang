#include <utility>

//
// Created by augusto.sigolo on 05/07/24.
//

class Block: public Interpreter_Graph{
    private:
        string name;
        Interpreter_Graph_Node* back_to = nullptr;
    public:
        explicit Block(string name) {
            this->name = std::move(name);
        }

        string get_name() {
            return this->name;
        }

        void set_back_to(Interpreter_Graph_Node* back_to) {
            this->back_to = back_to;
        }

        Interpreter_Graph_Node* get_back_to() {
            return this->back_to;
        }
};