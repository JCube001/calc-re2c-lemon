%include
{

#include "calc.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct state
{
    struct calc_expr *root;
    bool error;
};

}

%token_type {union calc_token *}
%default_type {struct calc_expr *}

%extra_argument {struct state *state}

%destructor expr { calc_expr_destroy($$); }

%left PLUS MINUS.
%left TIMES DIVIDE.
%right EXPONENT POSITIVE NEGATIVE.

start ::= expr(A).
{
    state->root = A;
}

expr(A) ::= expr(B) PLUS expr(C).
{
    A = calc_expr_create_binop(CALC_EXPR_ADD, B, C);
}

expr(A) ::= expr(B) MINUS expr(C).
{
    A = calc_expr_create_binop(CALC_EXPR_SUB, B, C);
}

expr(A) ::= expr(B) TIMES expr(C).
{
    A = calc_expr_create_binop(CALC_EXPR_MUL, B, C);
}

expr(A) ::= expr(B) DIVIDE expr(C).
{
    A = calc_expr_create_binop(CALC_EXPR_DIV, B, C);
}

expr(A) ::= expr(B) EXPONENT expr(C).
{
    A = calc_expr_create_binop(CALC_EXPR_POW, B, C);
}

expr(A) ::= LPAREN expr(B) RPAREN.
{
    A = B;
}

expr(A) ::= PLUS expr(B). [POSITIVE]
{
    A = B;
}

expr(A) ::= MINUS expr(B). [NEGATIVE]
{
    A = calc_expr_create_unop(CALC_EXPR_NEG, B);
}

expr(A) ::= NUMBER(B).
{
    A = calc_expr_create_num(B->num);
}

%syntax_error
{
    state->error = true;
    puts("Syntax error");
}

%parse_failure
{
    puts("Parse failure");
}

%code
{

struct calc_expr *
calc_parse(const char *code)
{
    struct calc_lexer lexer;
    union calc_token token;
    struct state state;
    void *parser;
    int id;

    state.root = NULL;
    state.error = false;

    calc_lexer_init(&lexer, code);
    parser = ParseAlloc(malloc);
    if (parser == NULL) {
        return NULL;
    }

    do {
        id = calc_lexer_next(&lexer, &token);
        Parse(parser, id, &token, &state);
    } while (id != 0);

    ParseFree(parser, free);

    return state.error ? NULL : state.root;
}

}
