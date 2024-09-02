#include <iostream>

bool equals(char *a, char *b){
    int n_a = sizeof(a)/sizeof(char);
    int n_b = sizeof(b)/sizeof(char);

}

void parseArgs(int argc, char **argv){
    for (int i=0; i < argc; i++)
        std::cout << argv[i] << std::endl;
}


int main(int argc, char **argv){
    std::cout << "Hello World" << std::endl;
    parseArgs(argc, argv);    
}