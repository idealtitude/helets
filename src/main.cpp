#include <iostream>
#include <fstream>
#include "AST.hpp"

extern FILE* yyin;
extern int yyparse();
extern ProgramNode* getProgram();

void printHelp()
{
    std::cout << "Helets Programming Language" << '\n';
    std::cout << "Usage: helets <filename>" << '\n';
}

int main(int argc, char** argv)
{
    if (argc != 2)
	{
        std::cerr << "Error: Expected a filename" << '\n';
        printHelp();
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file)
	{
        std::cerr << "Error: Could not open file " << argv[1] << '\n';
        return 1;
    }

    yyin = file;
    std::cout << "Parsing " << argv[1] << "..." << '\n';

    if (yyparse() == 0)
	{
        std::cout << "Parsing successful!" << '\n';

        // Get the program AST and print it
        ProgramNode* program = getProgram();
        if (program) {
            std::cout << "\nAST Structure:" << '\n';
            program->print();
        }
    }
	else
	{
        std::cerr << "Parsing failed." << '\n';
        return 1;
    }

    fclose(file);
    return 0;
}
