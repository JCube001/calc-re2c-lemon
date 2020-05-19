#ifndef CALC_LEXER_H
#define CALC_LEXER_H

#include "token.h"

// These standard C includes and declaring the parser state must come before
// including the parser interface
//#include <stddef.h>
//#include <stdio.h>

//struct state;

#include "parser.h"

struct calc_lexer
{
    const char *cursor;
    const char *marker;
};

#ifdef __cplusplus
extern "C" {
#endif

void
calc_lexer_init(struct calc_lexer *lexer,
                const char *input);

int
calc_lexer_next(struct calc_lexer *lexer,
                union calc_token *token);

#ifdef __cplusplus
}
#endif

#endif /* CALC_LEXER_H */
