#include "calc.h"
#include "config.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define EOT (4)

static const char *
skip_ws(const char *s)
{
    while (isspace(*s)) ++s;
    return s;
}

int
main(void)
{
    int rc;

    printf("Calc interpreter version " CALC_VERSION "\n"
           "Enter " CALC_KEYSEQ_QUIT " to quit\n");

    for (;;) {
        const char *input;
        char line[80];
        double result;

        printf("> ");
        fflush(stdout);
        fgets(line, sizeof(line), stdin);

        input = skip_ws(line);
        if ((EOT == *input) || feof(stdin)) break;
        if ('\n' == *input) continue;

        rc = calc_eval(&result, input);
        if (rc != 0) continue;

        printf("%g\n", result);
    }

    puts("\nBye!");
    return EXIT_SUCCESS;
}
