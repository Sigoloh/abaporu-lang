#include <iostream>
#include <cstring>
#include <fstream>
#include <regex>
#include <vector>
#include "./interpreter_graph.cpp"
#include "./runner.cpp"
#include "./compiler.cpp"
using namespace std;

vector<string> prepare_instructions(const string& file_path){
    regex color_pattern("#[0-9A-F]{6}", regex_constants::icase);
    string whole_file;
    string text_input;

    ifstream input_file(file_path);

    while(getline(input_file, text_input)){
        whole_file += text_input;
    }

    auto instructions_begin = sregex_iterator(whole_file.begin(), whole_file.end(), color_pattern);

    auto instructions_end = sregex_iterator();

    vector<string> instruction_vector;

    for(sregex_iterator i = instructions_begin; i != instructions_end; i++){
        const smatch& color_match = *i;
        instruction_vector.push_back(color_match.str());
    }

    return instruction_vector;
}

void get_arguments(int argc, char *argv[], char ***input_target, char ***output_target){

    for(int i = 0; i < argc; i++) {
        if(strcmp("-i", argv[i]) == 0){
            *input_target = &argv[i+1];
        }

        if(strcmp("-o", argv[i]) == 0){
            *output_target = &argv[i+1];
        }
    }
}

void interpret(Interpreter_Graph* graph_to_use) {
    int sausage[graph_to_use->get_slots_needed()];

    for(int i = 0; i < graph_to_use->get_slots_needed(); ++i) {
        sausage[i] = 0;
    }


}

int main(const int argc, char *argv[]){

    char **input_target = nullptr;
    char **output_target = nullptr;

    get_arguments(argc, argv, &input_target, &output_target);

    if(input_target == nullptr){
        cout<<"[USER ERROR] No input file provided"<<endl;
        return 1;
    }

    if(output_target == nullptr){
        // cout<<"[WARNING] No output file provided. You will not be able to receive your art after this process"<<endl;
    }

    vector<string> instructions_vec = prepare_instructions(*input_target);;

    const auto graph = new Interpreter_Graph();

    for(const auto& instruction : instructions_vec){
        graph->handle_instruction(instruction);
    }

    auto runner = new Runner(graph);

    auto compiler = new Compiler(graph);

    runner->run();

    compiler->compile();
    return 0;
}