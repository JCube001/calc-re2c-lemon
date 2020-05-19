#include "lexer.h"

#include <stdlib.h>

void
calc_lexer_init(struct calc_lexer *lexer,
                const char *input)
{
    lexer->cursor = input;
}

int
calc_lexer_next(struct calc_lexer *lexer,
                union calc_token *token)
{
    const char *lexeme;

loop:
    lexeme = lexer->cursor;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = lexer->cursor;
        re2c:define:YYMARKER = lexer->marker;
        re2c:yyfill:enable = 0;

        ws     = [ \t\v\f\r\n]+;
        number = [-+]?([0-9]+([.][0-9]*)?|[.][0-9]+)([Ee][-+]?[0-9]+)?;

        *   { return 0; }
        ws  { goto loop; }

        "+" { return PLUS; }
        "-" { return MINUS; }
        "*" { return TIMES; }
        "/" { return DIVIDE; }
        "^" { return EXPONENT; }
        "(" { return LPAREN; }
        ")" { return RPAREN; }

        number
        {
            token->num = atof(lexeme);
            return NUMBER;
        }
    */
}
