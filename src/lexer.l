%{
#include "parser.tab.h"
%}

%option noyywrap

%%

" "      ;
"\t"     ;
"\n"     ;

"+"      return PLUS;
"-"      return MINUS;
"*"      return TIMES;
"/"      return DIVIDE;
"("      return LPAREN;
")"      return RPAREN;
";"      return SEMICOLON;

[0-9]+   { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { strncpy(yylval.string, yytext, MAX_IDENTIFIER_LENGTH); return IDENTIFIER; }

.        { printf("Invalid character: %s\n", yytext); }

%%
