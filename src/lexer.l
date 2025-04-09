%{
#include <string>
#include "AST.hpp"
#include "parser.tab.hpp"

#define YY_DECL int yylex()

extern int yylineno;
%}

%option noyywrap
%option yylineno

%%
[ \t]+          ; // Ignore whitespace
\n              { return NEWLINE; }

"//"[^\n]*      ; // Single line comments

"int"           { return TYPE_INT; }
"float"         { return TYPE_FLOAT; }
"bool"          { return TYPE_BOOL; }
"str"           { return TYPE_STR; }

"true"          { yylval.bool_val = true; return BOOL_LIT; }
"false"         { yylval.bool_val = false; return BOOL_LIT; }

":"             { return COLON; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }

"("             { return '('; }
")"             { return ')'; }

[0-9]+          { 
                  yylval.int_val = std::stoi(yytext); 
                  return INT_LIT; 
                }

[0-9]+\.[0-9]+  { 
                  yylval.float_val = std::stof(yytext); 
                  return FLOAT_LIT; 
                }

\"[^\"]*\"      {
                  // Remove the quotes
                  std::string str(yytext+1);
                  str.pop_back();
                  yylval.str_val = strdup(str.c_str());
                  return STR_LIT;
                }

[a-zA-Z][a-zA-Z0-9_]* {
                  yylval.str_val = strdup(yytext);
                  return IDENTIFIER;
                }

.               { return yytext[0]; }
%%
