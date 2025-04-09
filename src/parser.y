%{
#include <iostream>
#include <string>
#include "AST.hpp"

extern int yylex();
extern int yylineno;
extern FILE* yyin;

void yyerror(const char* s);

// Root of the AST
ProgramNode* program = new ProgramNode();
%}

%union {
    int int_val;
    float float_val;
    bool bool_val;
    char* str_val;
    ExprNode* expr;
    StmtNode* stmt;
    VarDeclNode* var_decl;
}

%token <int_val> INT_LIT
%token <float_val> FLOAT_LIT
%token <bool_val> BOOL_LIT
%token <str_val> STR_LIT
%token <str_val> IDENTIFIER
%token TYPE_INT TYPE_FLOAT TYPE_BOOL TYPE_STR
%token COLON NEWLINE

%type <expr> expr
%type <stmt> statement
%type <var_decl> var_declaration

// Define operator precedence (lower = higher precedence)
%left '+' '-'
%left '*' '/'

%%
program:
    statement               { program->addStatement($1); }
    | program statement     { program->addStatement($2); }
    ;

statement:
    var_declaration NEWLINE  { $$ = $1; }
    | NEWLINE               { $$ = nullptr; }
    ;

var_declaration:
    TYPE_INT IDENTIFIER COLON expr     { $$ = new VarDeclNode(DataType::INT, $2, $4); }
    | TYPE_FLOAT IDENTIFIER COLON expr { $$ = new VarDeclNode(DataType::FLOAT, $2, $4); }
    | TYPE_BOOL IDENTIFIER COLON expr  { $$ = new VarDeclNode(DataType::BOOL, $2, $4); }
    | TYPE_STR IDENTIFIER COLON expr   { $$ = new VarDeclNode(DataType::STRING, $2, $4); }
    ;

expr:
    INT_LIT     { $$ = new IntLiteralNode($1); }
    | FLOAT_LIT { $$ = new FloatLiteralNode($1); }
    | BOOL_LIT  { $$ = new BoolLiteralNode($1); }
    | STR_LIT   { $$ = new StringLiteralNode($1); }
    | expr '+' expr { $$ = new BinaryOpNode(OpType::ADD, $1, $3); }
    | expr '-' expr { $$ = new BinaryOpNode(OpType::SUB, $1, $3); }
    | expr '*' expr { $$ = new BinaryOpNode(OpType::MUL, $1, $3); }
    | expr '/' expr { $$ = new BinaryOpNode(OpType::DIV, $1, $3); }
    | '(' expr ')'  { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    std::cerr << "Parse error at line " << yylineno << ": " << s << std::endl;
}

ProgramNode* getProgram() {
    return program;
}
