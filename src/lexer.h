#ifndef CALC_LEXER_H
#define CALC_LEXER_H

#include "token.h"
#include <stdio.h>

struct calc_lexer
{
    const char *cursor;
    const char *marker;
    FILE *diag;
};

#ifdef __cplusplus
extern "C" {
#endif

void
calc_lexer_init(struct calc_lexer *lexer,
                const char        *input,
                FILE              *diag);

int
calc_lexer_next(struct calc_lexer *lexer,
                union calc_token  *token);

#ifdef __cplusplus
}
#endif

#endif /* CALC_LEXER_H */
