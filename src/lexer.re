#include "lexer.h"

#include "grammar.h"
#include <stdarg.h>
#include <stdlib.h>

void
error(struct calc_lexer *lexer,
      const char        *fmt,
      ...)
{
    va_list args;
    fprintf(lexer->diag, "error: ");
    va_start(args, fmt);
    vfprintf(lexer->diag, fmt, args);
    va_end(args);
}

void
calc_lexer_init(struct calc_lexer *lexer,
                const char        *input,
                FILE              *diag)
{
    lexer->cursor = input;
    lexer->diag = diag;
}

int
calc_lexer_next(struct calc_lexer *lexer,
                union calc_token  *token)
{
    const char *lexeme;

loop:
    lexeme = lexer->cursor;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = lexer->cursor;
        re2c:define:YYMARKER = lexer->marker;
        re2c:yyfill:enable = 0;

        *      { error(lexer, "stray '%c' detected\n", yych); goto loop; }
        "\x00" { return 0; }

        [ \t\r\n]+ { goto loop; }

        "+" { return PLUS; }
        "-" { return MINUS; }
        "*" { return TIMES; }
        "/" { return DIVIDE; }
        "(" { return LPAREN; }
        ")" { return RPAREN; }

        [0-9]+ ("." [0-9]+)?
        {
            token->number = strtod(lexeme, NULL);
            return NUMBER;
        }
    */
}
