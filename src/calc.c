#include "calc.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

static double
eval(struct calc_expr *const expr)
{
    assert(expr != NULL);

    double result;

    switch (expr->type) {
    case CALC_EXPR_ADD:
        result = eval(expr->binop.lhs) + eval(expr->binop.rhs);
        break;
    case CALC_EXPR_SUB:
        result = eval(expr->binop.lhs) - eval(expr->binop.rhs);
        break;
    case CALC_EXPR_MUL:
        result = eval(expr->binop.lhs) * eval(expr->binop.rhs);
        break;
    case CALC_EXPR_DIV:
        result = eval(expr->binop.lhs) / eval(expr->binop.rhs);
        break;
    case CALC_EXPR_POW:
        result = pow(eval(expr->binop.lhs), eval(expr->binop.rhs));
        break;
    case CALC_EXPR_NEG:
        result = -eval(expr->unop.rhs);
        break;
    case CALC_EXPR_NUM:
        result = expr->num;
        break;
    default:
        result = nan("");
        break;
    }

    return result;
}

struct calc_expr *
calc_expr_create_num(const double value)
{
    struct calc_expr *expr;

    expr = malloc(sizeof(*expr));
    if (expr != NULL) {
        expr->type = CALC_EXPR_NUM;
        expr->num = value;
    }

    return expr;
}

struct calc_expr *
calc_expr_create_unop(const enum calc_expr_type type,
                      struct calc_expr *const rhs)
{
    struct calc_expr *expr;

    expr = malloc(sizeof(*expr));
    if (expr != NULL) {
        expr->type = type;
        expr->unop.rhs = rhs;
    }

    return expr;
}

struct calc_expr *
calc_expr_create_binop(const enum calc_expr_type type,
                       struct calc_expr *const lhs,
                       struct calc_expr *const rhs)
{
    struct calc_expr *expr;

    expr = malloc(sizeof(*expr));
    if (expr != NULL) {
        expr->type = type;
        expr->binop.lhs = lhs;
        expr->binop.rhs = rhs;
    }

    return expr;
}

void
calc_expr_destroy(struct calc_expr *const expr)
{
    switch (expr->type) {
    case CALC_EXPR_ADD:
    case CALC_EXPR_SUB:
    case CALC_EXPR_MUL:
    case CALC_EXPR_DIV:
    case CALC_EXPR_POW:
        calc_expr_destroy(expr->binop.lhs);
        calc_expr_destroy(expr->binop.rhs);
        break;
    case CALC_EXPR_NEG:
        calc_expr_destroy(expr->unop.rhs);
        break;
    default:
        break;
    }

    free(expr);
}

int
calc_eval(double *result,
          const char *code)
{
    struct calc_expr *expr;

    expr = calc_parse(code);
    if (expr == NULL) {
        return -1;
    }

    *result = eval(expr);
    return 0;
}
