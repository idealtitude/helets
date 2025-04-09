#include <iostream>
#include <fstream>
#include "AST.hpp"

extern FILE* yyin;
extern int yyparse();
extern ProgramNode* getProgram();

void printHelp() {
    std::cout << "Helets Programming Language" << std::endl;
    std::cout << "Usage: helets <filename>" << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error: Expected a filename" << std::endl;
        printHelp();
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    yyin = file;
    std::cout << "Parsing " << argv[1] << "..." << std::endl;

    if (yyparse() == 0) {
        std::cout << "Parsing successful!" << std::endl;
        
        // Get the program AST and print it
        ProgramNode* program = getProgram();
        if (program) {
            std::cout << "\nAST Structure:" << std::endl;
            program->print();
        }
    } else {
        std::cerr << "Parsing failed." << std::endl;
        return 1;
    }

    fclose(file);
    return 0;
}
