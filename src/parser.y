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
    IfStmtNode* if_stmt;
}

%token <int_val> INT_LIT
%token <float_val> FLOAT_LIT
%token <bool_val> BOOL_LIT
%token <str_val> STR_LIT
%token <str_val> IDENTIFIER
%token TYPE_INT TYPE_FLOAT TYPE_BOOL TYPE_STR
%token COLON NEWLINE
%token IF ELSE
%token EQ NEQ GT GTE LT LTE

%type <expr> expr condition
%type <stmt> statement block_statement
%type <var_decl> var_declaration
%type <if_stmt> if_statement

// Define operator precedence (lower = higher precedence)
%left EQ NEQ
%left GT GTE LT LTE
%left '+' '-'
%left '*' '/'

%%
program:
    statement               { if ($1 != nullptr) program->addStatement($1); }
    | program statement     { if ($2 != nullptr) program->addStatement($2); }
    ;

statement:
    var_declaration NEWLINE  { $$ = $1; }
    | if_statement          { $$ = $1; }
    | NEWLINE               { $$ = nullptr; }
    ;

block_statement:
    var_declaration NEWLINE  { $$ = $1; }
    ;

var_declaration:
    TYPE_INT IDENTIFIER COLON expr     { $$ = new VarDeclNode(DataType::INT, $2, $4); }
    | TYPE_FLOAT IDENTIFIER COLON expr { $$ = new VarDeclNode(DataType::FLOAT, $2, $4); }
    | TYPE_BOOL IDENTIFIER COLON expr  { $$ = new VarDeclNode(DataType::BOOL, $2, $4); }
    | TYPE_STR IDENTIFIER COLON expr   { $$ = new VarDeclNode(DataType::STRING, $2, $4); }
    | IDENTIFIER COLON expr            { $$ = new VarDeclNode(DataType::INT, $1, $3); } // For assignments in if/else blocks
    ;

if_statement:
    IF '(' condition ')' COLON NEWLINE block_statement
        { $$ = new IfStmtNode($3, $7, nullptr); }
    | IF '(' condition ')' COLON NEWLINE block_statement ELSE COLON NEWLINE block_statement
        { $$ = new IfStmtNode($3, $7, $11); }
    ;

condition:
    expr                    { $$ = $1; }
    ;

expr:
    INT_LIT     { $$ = new IntLiteralNode($1); }
    | FLOAT_LIT { $$ = new FloatLiteralNode($1); }
    | BOOL_LIT  { $$ = new BoolLiteralNode($1); }
    | STR_LIT   { $$ = new StringLiteralNode($1); }
    | IDENTIFIER { $$ = new IdentifierNode($1); }
    | expr '+' expr { $$ = new BinaryOpNode(OpType::ADD, $1, $3); }
    | expr '-' expr { $$ = new BinaryOpNode(OpType::SUB, $1, $3); }
    | expr '*' expr { $$ = new BinaryOpNode(OpType::MUL, $1, $3); }
    | expr '/' expr { $$ = new BinaryOpNode(OpType::DIV, $1, $3); }
    | expr EQ expr  { $$ = new BinaryOpNode(OpType::EQ, $1, $3); }
    | expr NEQ expr { $$ = new BinaryOpNode(OpType::NEQ, $1, $3); }
    | expr GT expr  { $$ = new BinaryOpNode(OpType::GT, $1, $3); }
    | expr GTE expr { $$ = new BinaryOpNode(OpType::GTE, $1, $3); }
    | expr LT expr  { $$ = new BinaryOpNode(OpType::LT, $1, $3); }
    | expr LTE expr { $$ = new BinaryOpNode(OpType::LTE, $1, $3); }
    | '(' expr ')'  { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    std::cerr << "Parse error at line " << yylineno << ": " << s << std::endl;
}

ProgramNode* getProgram() {
    return program;
}
