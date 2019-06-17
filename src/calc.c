#include "calc.h"

#include "lexer.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct parser_state
{
    FILE *diag;
    bool error;
};

/* Include the auto-generated parser implementation */
#define Parse_ENGINEALWAYSONSTACK
#include "grammar.c"

struct calc_expr *
calc_expr_create_number(const double number)
{
    struct calc_expr *expr;

    expr = malloc(sizeof(*expr));
    if (expr) {
        expr->type = CALC_EXPR_NUM;
        expr->number = number;
    }

    return expr;
}

struct calc_expr *
calc_expr_create_unary(const enum calc_expr_type  type,
                       struct calc_expr          *rhs)
{
    struct calc_expr *expr;

    expr = malloc(sizeof(*expr));
    if (expr) {
        expr->type = type;
        expr->unary.rhs = rhs;
    }

    return expr;
}

struct calc_expr*
calc_expr_create_binary(const enum calc_expr_type  type,
                        struct calc_expr          *lhs,
                        struct calc_expr          *rhs)
{
    struct calc_expr *expr;

    expr = malloc(sizeof(*expr));
    if (expr) {
        expr->type = type;
        expr->binary.lhs = lhs;
        expr->binary.rhs = rhs;
    }

    return expr;
}

void
calc_expr_destroy(struct calc_expr *expr)
{
    assert(expr != NULL);

    switch (expr->type) {
    case CALC_EXPR_ADD:
    case CALC_EXPR_SUB:
    case CALC_EXPR_MUL:
    case CALC_EXPR_DIV:
        calc_expr_destroy(expr->binary.lhs);
        calc_expr_destroy(expr->binary.rhs);
        break;
    case CALC_EXPR_NEG:
        calc_expr_destroy(expr->unary.rhs);
        break;
    default:
        break;
    }

    free(expr);
}

double
calc_expr_eval(const struct calc_expr *expr)
{
    assert(expr != NULL);

    switch (expr->type) {
    case CALC_EXPR_ADD:
        return calc_expr_eval(expr->binary.lhs) + calc_expr_eval(expr->binary.rhs);
    case CALC_EXPR_SUB:
        return calc_expr_eval(expr->binary.lhs) - calc_expr_eval(expr->binary.rhs);
    case CALC_EXPR_MUL:
        return calc_expr_eval(expr->binary.lhs) * calc_expr_eval(expr->binary.rhs);
    case CALC_EXPR_DIV:
        return calc_expr_eval(expr->binary.lhs) / calc_expr_eval(expr->binary.rhs);
    case CALC_EXPR_NEG:
        return -calc_expr_eval(expr->unary.rhs);
    case CALC_EXPR_NUM:
        return expr->number;
    default:
        return nan("");
    }
}

struct calc_expr *
calc_parse(const char *input,
           FILE       *diag)
{
    assert(input != NULL);
    assert(diag != NULL);

    yyParser parser;
    struct calc_lexer lexer;
    union calc_token token;
    struct calc_expr *tree = NULL;
    struct parser_state state;
    int id;

    calc_lexer_init(&lexer, input, diag);
    ParseInit(&parser, &tree);
    state.diag = diag;
    state.error = false;

    do {
        id = calc_lexer_next(&lexer, &token);
        Parse(&parser, id, &token, &state);
        if (state.error) return NULL;
    } while (id != 0);

    ParseFinalize(&parser);

    return tree;
}

double
calc_eval(const char *input,
          FILE       *diag)
{
    struct calc_expr *tree = calc_parse(input, diag);
    if (NULL == tree) return nan("");
    const double result = calc_expr_eval(tree);
    calc_expr_destroy(tree);
    return result;
}
