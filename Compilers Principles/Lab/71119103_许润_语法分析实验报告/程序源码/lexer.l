%{
#include <stdio.h>
enum tag{
    IF, ELSE, DO, WHILE, BREAK,
    ID, NUM, ASSIGN, RELOP,
    PLUS, MINUS, TIMES, DIVIDE,
    SEMI, LPARA, RPARA, LBRACE, RBRACE
};
int yylex();
extern int line;
%}

space   (\ |\t)+
id      [A-Za-z][0-9A-Za-z]*
num     [0-9]+

%%
{space}    {}
"\n"       { line++; }

if         { printf("\033[0;32m[if]      %s\033[0m\n", yytext); return IF; }
else       { printf("\033[0;32m[else]    %s\033[0m\n", yytext); return ELSE; }
do         { printf("\033[0;32m[do]      %s\033[0m\n", yytext); return DO; }
while      { printf("\033[0;32m[while]   %s\033[0m\n", yytext); return WHILE; }
break      { printf("\033[0;32m[break]   %s\033[0m\n", yytext); return BREAK; }

{id}       { printf("\033[0;32m[id]      %s\033[0m\n", yytext); return ID; }
{num}      { printf("\033[0;32m[num]     %s\033[0m\n", yytext); return NUM; }

"=="       { printf("\033[0;32m[relop]   %s\033[0m\n", yytext); return RELOP; }
"!="       { printf("\033[0;32m[relop]   %s\033[0m\n", yytext); return RELOP; }
"<"        { printf("\033[0;32m[relop]   %s\033[0m\n", yytext); return RELOP; }
"<="       { printf("\033[0;32m[relop]   %s\033[0m\n", yytext); return RELOP; }
">"        { printf("\033[0;32m[relop]   %s\033[0m\n", yytext); return RELOP; }
">="       { printf("\033[0;32m[relop]   %s\033[0m\n", yytext); return RELOP; }

"="        { printf("\033[0;32m[assign]  %s\033[0m\n", yytext); return ASSIGN; }
"+"        { printf("\033[0;32m[plus]    %s\033[0m\n", yytext); return PLUS; }
"-"        { printf("\033[0;32m[minus]   %s\033[0m\n", yytext); return MINUS; }
"*"        { printf("\033[0;32m[times]   %s\033[0m\n", yytext); return TIMES; }
"/"        { printf("\033[0;32m[divide]  %s\033[0m\n", yytext); return DIVIDE; }
";"        { printf("\033[0;32m[semi]    %s\033[0m\n", yytext); return SEMI; }
"("        { printf("\033[0;32m[lpara]   %s\033[0m\n", yytext); return LPARA; }
")"        { printf("\033[0;32m[rpara]   %s\033[0m\n", yytext); return RPARA; }
"{"        { printf("\033[0;32m[lbrace]  %s\033[0m\n", yytext); return LBRACE; }
"}"        { printf("\033[0;32m[rbrace]  %s\033[0m\n", yytext); return RBRACE; }
%%
