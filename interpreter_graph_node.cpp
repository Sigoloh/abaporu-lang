//
// Created by augusto.sigolo on 03/07/24.
//
#include <cstring>
#include <iostream>
#include <utility>
using namespace std;

class Interpreter_Graph_Node{
    private:
         string instruction;
         Interpreter_Graph_Node* next;
         Interpreter_Graph_Node* prev;
         int aux = 0;
         string operation;
    public:
        Interpreter_Graph_Node(string instruction, string operation, int aux = -1){
           this->instruction = std::move(instruction);
           this->operation = std::move(operation);
           this->aux = aux;
           this->next = nullptr;
           this->prev = nullptr;
        }

        ~Interpreter_Graph_Node(){
            delete this;
        }

        void set_next(Interpreter_Graph_Node* next_to_set){
            this->next = next_to_set;
       }

        void set_prev(Interpreter_Graph_Node* prev_to_set){
            this->prev = prev_to_set;
        }

        Interpreter_Graph_Node* get_next(){
            return this->next;
        }

        Interpreter_Graph_Node* get_prev(){
            return this->prev;
        }

        string get_operation() {
            return this->operation;
        }

        [[nodiscard]] int get_aux() const {
            return this->aux;
        }

        void see_resume(){
            cout<<"Instruction "<<this->instruction<<endl;
            cout<<"Opperation "<<this->operation<<endl;
            cout<<"Aux "<<this->aux<<endl;
        }
};