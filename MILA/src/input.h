#ifndef MILA_INPUT_H
#define MILA_INPUT_H

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Read one bounded integer token; reject malformed and oversized input. */
static inline int read_int(int *value, int minimum, int maximum)
{
    char token[64];
    size_t length = 0;
    int ch;
    int too_long = 0;
    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));
    if (ch == EOF) return 0;
    do {
        if (length + 1 < sizeof token) token[length++] = (char)ch;
        else too_long = 1;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));
    token[length] = '\0';
    if (too_long) return 0;
    errno = 0;
    char *end;
    long parsed = strtol(token, &end, 10);
    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < minimum || parsed > maximum) return 0;
    *value = (int)parsed;
    return 1;
}

static inline int input_error(void)
{
    fputs("Invalid input\n", stderr);
    return EXIT_FAILURE;
}

static inline int input_finished(void)
{
    int ch;
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) return 0;
    }
    return !ferror(stdin);
}
#endif
