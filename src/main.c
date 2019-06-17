#include "calc.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

#define EOT 4

static const char *
trim(const char *str)
{
loop:
    switch (*str) {
    case ' ':
    case '\f':
    case '\v':
    case '\t':
    case '\r':
        ++str;
        goto loop;
    default:
        return str;
    }
}

int main(void)
{
    printf("Calc interpreter version " CALC_VERSION "\n"
           "Enter " CALC_KEYSEQ_QUIT " to quit\n");

    for (;;) {
        const char *input;
        char line[80];

        printf("> ");
        fflush(stdout);
        fgets(line, sizeof(line), stdin);

        input = trim(line);
        if ((EOT == *input) || feof(stdin)) break;
        if ('\n' == *input) continue;

        printf("%g\n", calc_eval(input, stderr));
    }

    puts("Bye!");
    return EXIT_SUCCESS;
}
