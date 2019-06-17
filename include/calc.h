#ifndef CALC_H
#define CALC_H

#include <stdio.h>

enum calc_expr_type
{
    CALC_EXPR_ADD,
    CALC_EXPR_SUB,
    CALC_EXPR_MUL,
    CALC_EXPR_DIV,
    CALC_EXPR_NEG,
    CALC_EXPR_NUM,
};

struct calc_expr
{
    enum calc_expr_type type;
    union {
        double number;
        struct {
            struct calc_expr *rhs;
        } unary;
        struct {
            struct calc_expr *lhs;
            struct calc_expr *rhs;
        } binary;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

struct calc_expr *
calc_expr_create_number(const double number);

struct calc_expr *
calc_expr_create_unary(const enum calc_expr_type  type,
                       struct calc_expr          *rhs);

struct calc_expr*
calc_expr_create_binary(const enum calc_expr_type  type,
                        struct calc_expr          *lhs,
                        struct calc_expr          *rhs);

void
calc_expr_destroy(struct calc_expr *expr);

double
calc_expr_eval(const struct calc_expr *expr);

struct calc_expr *
calc_parse(const char *input,
           FILE       *diag);

double
calc_eval(const char *input,
          FILE       *diag);

#ifdef __cplusplus
}
#endif

#endif /* CALC_H */
