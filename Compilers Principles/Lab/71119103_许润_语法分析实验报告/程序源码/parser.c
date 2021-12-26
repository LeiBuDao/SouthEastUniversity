#include <stdio.h>
#include <stdlib.h>

enum tag{
    IF, ELSE, DO, WHILE, BREAK,
    ID, NUM, ASSIGN, RELOP,
    PLUS, MINUS, TIMES, DIVIDE,
    SEMI, LPARA, RPARA, LBRACE, RBRACE
};
int yylex();
void factor();
void rterm();
void term();
void rexpr();
void expr();
void rboolean();
void boolean();
void else_part();
void stmt();
void stmts();
void block();

int line = 1;
int lookahead;

void throw_exception()
{
    printf("\033[0;31msyntax error at line %d\033[0m\n", line);
    exit(1);
}

void match(int tag)
{
    if (lookahead == tag)
        lookahead = yylex();
    else
        throw_exception();
}

/* ----------------------------------- */

void factor()
{
    switch (lookahead)
    {
    case LPARA:
        printf("\033[0;34mfactor    -> \033[1;34m(\033[0;34m expr \033[1;34m)\033[0m\n");
        match(LPARA);
        expr();
        match(RPARA);
        break;
    case ID:
        printf("\033[0;34mfactor    -> \033[1;34mid\033[0m\n");
        match(ID);
        break;
    case NUM:
        printf("\033[0;34mfactor    -> \033[1;34mnum\033[0m\n");
        match(NUM);
        break;
    default:
        throw_exception();
    }
}

void rterm()
{
    switch (lookahead)
    {
    case TIMES:
        printf("\033[0;34mrterm     -> \033[1;34m*\033[0;34m factor rterm\033[0m\n");
        match(TIMES);
        factor();
        rterm();
        break;
    case DIVIDE:
        printf("\033[0;34mrterm     -> \033[1;34m/\033[0;34m factor rterm\033[0m\n");
        match(DIVIDE);
        factor();
        rterm();
        break;
    case RELOP:
    case PLUS:
    case MINUS:
    case RPARA:
    case SEMI:
        printf("\033[0;34mrterm     -> ε\033[0m\n");
        break;
    default:
        throw_exception();
    }
}

void term()
{
    switch (lookahead)
    {
    case ID:
    case NUM:
    case LPARA:
        printf("\033[0;34mterm      -> factor rterm\033[0m\n");
        factor();
        rterm();
        break;
    default:
        throw_exception();
    }
}

void rexpr()
{
    switch (lookahead)
    {
    case PLUS:
        printf("\033[0;34mrexpr     -> \033[1;34m+\033[0;34m term rexpr\033[0m\n");
        match(PLUS);
        term();
        rexpr();
        break;
    case MINUS:
        printf("\033[0;34mrexpr     -> \033[1;34m-\033[0;34m term rexpr\033[0m\n");
        match(MINUS);
        term();
        rexpr();
        break;
    case RELOP:
    case RPARA:
    case SEMI:
        printf("\033[0;34mrexpr     -> ε\033[0m\n");
        break;
    default:
        throw_exception();
    }
}

void expr()
{
    switch (lookahead)
    {
    case ID:
    case NUM:
    case LPARA:
        printf("\033[0;34mexpr      -> term rexpr\033[0m\n");
        term();
        rexpr();
        break;
    default:
        throw_exception();
    }
}

void rboolean()
{
    switch (lookahead)
    {
    case RELOP:
        printf("\033[0;34mrboolean  -> \033[1;34mrelop\033[0;34m expr\033[0m\n");
        match(RELOP);
        expr();
        break;
    case RPARA:
        printf("\033[0;34mrboolean  -> ε\033[0m\n");
        break;
    default:
        throw_exception();
    }
}

void boolean()
{
    switch (lookahead)
    {
    case ID:
    case NUM:
    case LPARA:
        printf("\033[0;34mboolean   -> expr rboolean\033[0m\n");
        expr();
        rboolean();
        break;
    default:
        throw_exception();
    }
}

void else_part()
{
    switch (lookahead)
    {
    case ELSE:
        printf("\033[0;34melse_part -> \033[1;34melse\033[0;34m stmt\033[0m\n");
        match(ELSE);
        stmt();
        break;
    case ID:
    case IF:
    case WHILE:
    case DO:
    case BREAK:
    case LBRACE:
    case RBRACE:
        printf("\033[0;34melse_part -> ε\033[0m\n");
        break;
    default:
        throw_exception();
    }
}

void stmt()
{
    switch (lookahead)
    {
    case ID:
        printf("\033[0;34mstmt      -> \033[1;34mid\033[0;34m \033[1;34m=\033[0;34m expr\033[0m\n");
        match(ID);
        match(ASSIGN);
        expr();
        match(SEMI);
        break;
    case IF:
        printf("\033[0;34mstmt      -> \033[1;34mif\033[0;34m \033[1;34m(\033[0;34m boolean \033[1;34m)\033[0;34m stmt else_part\033[0m\n");
        match(IF);
        match(LPARA);
        boolean();
        match(RPARA);
        stmt();
        else_part();
        break;
    case WHILE:
        printf("\033[0;34mstmt      -> \033[1;34mwhile\033[0;34m \033[1;34m(\033[0;34m boolean \033[1;34m)\033[0;34m stmt\033[0m\n");
        match(WHILE);
        match(LPARA);
        boolean();
        match(RPARA);
        stmt();
        break;
    case DO:
        printf("\033[0;34mstmt      -> \033[1;34mdo\033[0;34m stmt \033[1;34mwhile\033[0;34m \033[1;34m(\033[0;34m boolean \033[1;34m)\033[0m\n");
        match(DO);
        stmt();
        match(WHILE);
        match(LPARA);
        boolean();
        match(RPARA);
        match(SEMI);
        break;
    case BREAK:
        printf("\033[0;34mstmt      -> \033[1;34mbreak\033[0m\n");
        match(BREAK);
        match(SEMI);
        break;
    case LBRACE:
        printf("\033[0;34mstmt      -> block\033[0m\n");
        block();
        break;
    default:
        throw_exception();
    }
}

void stmts()
{
    switch (lookahead)
    {
    case ID:
    case IF:
    case WHILE:
    case DO:
    case BREAK:
    case LBRACE:
        printf("\033[0;34mstmts     -> stmt stmts\033[0m\n");
        stmt();
        stmts();
        break;
    case RBRACE:
        printf("\033[0;34mstmts     -> ε\033[0m\n");
        break;
    default:
        throw_exception();
    }
}

void block()
{
    switch (lookahead)
    {
    case LBRACE:
        printf("\033[0;34mblock     -> \033[1;34m{\033[0;34m stmts \033[1;34m}\033[0m\n");
        match(LBRACE);
        stmts();
        match(RBRACE);
        break;
    default:
        throw_exception();
    }
}

int main()
{
    lookahead = yylex();
    switch (lookahead)
    {
    case LBRACE:
        printf("\033[0;34mprogram   -> block\033[0m\n");
        block();
        break;
    default:
        throw_exception();
    }
    return 0;
}