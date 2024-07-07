#include <iostream>
#include <cstring>
#include <fstream>
#include <regex>
#include <vector>
#include "./interpreter_graph.cpp"
#include "./runner.cpp"
#include "./compiler.cpp"
#include "./Image_Creation.cpp"
using namespace std;

bool check_file(const string& file_path) {
    int path_len = file_path.length();
    if(path_len < 5) {
        return false;
    }

    string path_ext = file_path.substr(path_len - 6, 6);
    if(path_ext != ".abapl") {
        return false;
    }

    ifstream input_file(file_path);

    if(!input_file.good()) {
        input_file.close();
        return false;
    }

    return true;
}

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

int get_arguments(
    int argc,
    char *argv[],
    char ***input_target,
    char ***output_target,
    vector<pair<string, char*>>* extra_options
){
    for(int i = 0; i < argc; i++) {
        if(strcmp("-i", argv[i]) == 0){
            *input_target = &argv[i+1];
        }

        if(strcmp("-o", argv[i]) == 0){
            *output_target = &argv[i+1];
        }

        if(strcmp("--mode", argv[i]) == 0 || strcmp("-m", argv[i]) == 0) {
            if(i + 1 >= argc) {
                cout<<"Flag "<<argv[i]<<" used without value!"<<endl;
                return 1;
            }
            pair<string, char*> extra_option = {"--mode", argv[i + 1]};
            extra_options->push_back(extra_option);
        }

        if(strcmp("--cpp-output", argv[i]) == 0 || strcmp("-cppo", argv[i]) == 0) {
            if(i + 1 >= argc) {
                cout<<"Flag "<<argv[i]<<" used without value!"<<endl;
                return 1;
            }
            pair<string, char*> extra_option = {"--cpp-output", argv[i + 1]};
            extra_options->push_back(extra_option);
        }

        if(strcmp("--help", argv[i]) == 0 || strcmp("-h", argv[i]) == 0) {
            pair<string, char*> extra_option = {"--help", new char[0]};
            extra_options->push_back(extra_option);
        }

        if(strcmp("--scale-factor", argv[i]) == 0 || strcmp("-sc", argv[i]) == 0) {
            if(i + 1 >= argc) {
                cout<<"Flag "<<argv[i]<<" used without value!"<<endl;
                return 1;
            }
            pair<string, char*> extra_option = {"--scale-factor", argv[i + 1]};

            extra_options->push_back(extra_option);
        }

    }

    return 0;
}

void print_help() {
    cout<<"Use: abapl -i [.abapl file] -o [path to save the art] [extra options]"<<endl;
    cout<<"Extra options:"<<endl;
    cout<<"--mode -m   value: "<<"compile | run"<<"   Choose the way abapl will handle your code. Default: run & compile"<<endl;
    cout<<"--cpp-output -cppo   value: "<<"path"<<"   Path to save the .cpp file after compilation. Default: [abapl-folder]/outputs/output.cpp"<<endl;
    cout<<"--scale-factor -sc value: "<<"integer"<<"  Scale factor of the outputed .bmp file. Default: 3"<<endl;
    cout<<"--help -h"<<"   Display this message"<<endl;
}

char* search_option(const string &option_to_search, const vector<pair<string, char*>>* options) {

    for(const auto & option : *options) {
        if(option.first == option_to_search) {
            return option.second;
        }
    }

    return nullptr;
}

int main(const int argc, char *argv[]){

    char **input_target = nullptr;
    char **output_target = nullptr;
    vector<pair<string, char*>> extra_options;
    int arguments_response = get_arguments(argc, argv, &input_target, &output_target, &extra_options);

    if(arguments_response != 0) {
        print_help();
        return arguments_response;
    }

    if(input_target == nullptr) {
        print_help();
        return 0;
    }

    if(search_option("help", &extra_options) != nullptr) {
        print_help();
        return 0;
    }

    if(!check_file(*input_target)) {
        cout<<"[INPUT ERROR] The path you entered is not good!"<<endl;
        cout<<"[INPUT ERROR] Check if "<<*input_target<<" exists and its a .abapl file"<<endl;
        print_help();
        return 1;
    }
    vector<string> instructions_vec = prepare_instructions(*input_target);;

    const auto graph = new Interpreter_Graph();

    for(const auto& instruction : instructions_vec){
        graph->handle_instruction(instruction);
    }

    auto runner = new Runner(graph);

    auto out_file = search_option("--cpp-output", &extra_options);

    Compiler* compiler;
    if(out_file != nullptr) {
        compiler = new Compiler(graph, out_file);
    }else {
        compiler = new Compiler(graph);
    }

    Image_Creation* image_creation;

    const int scale_factor = stoi(
        search_option("--scale-factor", &extra_options) != nullptr ?
        search_option("--scale-factor", &extra_options) :
        "3"
    );

    if(output_target != nullptr) {
        image_creation = new Image_Creation(instructions_vec, scale_factor, *output_target);
    }else {
        image_creation = new Image_Creation(instructions_vec, scale_factor);
    }

    clog<<"[INFO] Creating image..."<<endl;
    image_creation->create();
    cout<<"[INFO] Image saved: "<<*output_target<<endl;
    if(search_option("--mode", &extra_options) == nullptr) {
        runner->run();

        compiler->compile();

        return 0;
    }

    if(strcmp("run", search_option("--mode", &extra_options)) == 0) {
        runner->run();
        return 0;
    }

    if(strcmp("compile", search_option("--mode", &extra_options)) == 0) {
        compiler->compile();
        return 0;
    }

    if(strcmp("run", search_option("--mode", &extra_options)) != 0 && strcmp("compile", search_option("--mode", &extra_options)) != 0) {
        cout<<"Unkown mode option: "<<search_option("--mode", &extra_options)<<endl;
        print_help();
    }

}