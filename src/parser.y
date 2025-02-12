%{
#include <iostream>
#include <string>
#include <cstdlib>

#define MAX_IDENTIFIER_LENGTH 32

// Use std::string for identifiers
typedef union {
    int number;
    char string[MAX_IDENTIFIER_LENGTH]; // Still needed for yylval.string (Flex limitation)
    std::string identifier;        // More C++ like
} YYSTYPE;

// Use C++ iostream for error reporting
void yyerror(const char *s);

// Declare external C functions
extern int yylex();
extern char *yytext;

%}

%token NUMBER
%token IDENTIFIER
%token PLUS MINUS TIMES DIVIDE
%token LPAREN RPAREN
%token SEMICOLON

%left PLUS MINUS
%left TIMES DIVIDE

%%

program:
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    expression SEMICOLON
    { std::cout << "Result: " << $1 << std::endl; }
    ;

expression:
    expression PLUS expression   { $$ = $1 + $3; }
    | expression MINUS expression  { $$ = $1 - $3; }
    | expression TIMES expression  { $$ = $1 * $3; }
    | expression DIVIDE expression {
                                    if ($3 == 0) {
                                        yyerror("Division by zero");
                                        exit(1);
                                    }
                                    $$ = $1 / $3;
                                  }
    | LPAREN expression RPAREN   { $$ = $2; }
    | NUMBER                    { $$ = $1; }
    | IDENTIFIER                { /* Handle identifier lookup/value retrieval here */ $$ = 0; } // Placeholder
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Error: " << s << " near '" << yytext << "'" << std::endl;
}

int main() {
    yyparse();
    return 0;
}
