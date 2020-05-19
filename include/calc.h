#ifndef CALC_H
#define CALC_H

#include <stdio.h>

enum calc_expr_type
{
    CALC_EXPR_ADD,
    CALC_EXPR_SUB,
    CALC_EXPR_MUL,
    CALC_EXPR_DIV,
    CALC_EXPR_POW,
    CALC_EXPR_NEG,
    CALC_EXPR_NUM,
};

struct calc_expr
{
    enum calc_expr_type type;
    union {
        double num;
        struct {
            struct calc_expr *rhs;
        } unop;
        struct {
            struct calc_expr *lhs;
            struct calc_expr *rhs;
        } binop;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

struct calc_expr *
calc_expr_create_num(const double value);

struct calc_expr *
calc_expr_create_unop(const enum calc_expr_type type,
                      struct calc_expr *const rhs);

struct calc_expr *
calc_expr_create_binop(const enum calc_expr_type type,
                       struct calc_expr *const lhs,
                       struct calc_expr *const rhs);

void
calc_expr_destroy(struct calc_expr *const expr);

int
calc_eval(double *result,
          const char *code);

struct calc_expr *
calc_parse(const char *code);

#ifdef __cplusplus
}
#endif

#endif /* CALC_H */
