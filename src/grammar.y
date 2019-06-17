%include {
#include "calc.h"
#include "token.h"
#include <stdlib.h>
}

%token_type {union calc_token *}
%type expr {struct calc_expr *}

%destructor expr { calc_expr_destroy($$); }

%extra_context {struct calc_expr **tree}
%extra_argument {struct parser_state *state}

%left PLUS MINUS.
%left TIMES DIVIDE.
%right NEGATE.

prog ::= expr(A).                   { *tree = A; }
expr(A) ::= expr(B) PLUS expr(C).   { A = calc_expr_create_binary(CALC_EXPR_ADD, B, C); }
expr(A) ::= expr(B) MINUS expr(C).  { A = calc_expr_create_binary(CALC_EXPR_SUB, B, C); }
expr(A) ::= expr(B) TIMES expr(C).  { A = calc_expr_create_binary(CALC_EXPR_MUL, B, C); }
expr(A) ::= expr(B) DIVIDE expr(C). { A = calc_expr_create_binary(CALC_EXPR_DIV, B, C); }
expr(A) ::= LPAREN expr(B) RPAREN.  { A = B; }
expr(A) ::= MINUS expr(B). [NEGATE] { A = calc_expr_create_unary(CALC_EXPR_NEG, B); }
expr(A) ::= NUMBER(B).              { A = calc_expr_create_number(B->number); }

%syntax_error {
    state->error = true;
    fputs("error: bad input\n", state->diag);
}
