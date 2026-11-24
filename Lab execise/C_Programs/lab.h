#ifndef CSA0234_LAB_H
#define CSA0234_LAB_H
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LAB_CAP 100
#define LAB_TEXT 256

static inline void lab_require(int condition, const char *message)
{
    if (!condition)
    {
        fprintf(stderr, "Error: %s\n", message);
        exit(EXIT_FAILURE);
    }
}

static inline void lab_token(char token[LAB_TEXT])
{
    int ch;
    size_t size = 0;
    do
    {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));
    lab_require(ch != EOF, "missing input");
    while (ch != EOF && !isspace((unsigned char)ch))
    {
        lab_require(size + 1 < LAB_TEXT, "token too long");
        token[size++] = (char)ch;
        ch = getchar();
    }
    token[size] = '\0';
}

static inline long long lab_integer(long long minimum, long long maximum)
{
    char token[LAB_TEXT], *end;
    lab_token(token);
    errno = 0;
    long long value = strtoll(token, &end, 10);
    lab_require(errno != ERANGE && end != token && *end == '\0' && value >= minimum &&
                    value <= maximum,
                "integer outside allowed range");
    return value;
}

static inline int lab_int(int minimum, int maximum)
{
    return (int)lab_integer(minimum, maximum);
}

static inline double lab_real(double minimum, double maximum)
{
    char token[LAB_TEXT], *end;
    lab_token(token);
    errno = 0;
    double value = strtod(token, &end);
    lab_require(errno != ERANGE && end != token && *end == '\0' && isfinite(value) &&
                    value >= minimum && value <= maximum,
                "real number outside allowed range");
    return value;
}

static inline void lab_line(char text[LAB_TEXT])
{
    size_t n = 0;
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n')
    {
        lab_require(n + 1 < LAB_TEXT, "text line too long");
        text[n++] = (char)ch;
    }
    lab_require(ch != EOF || n > 0, "missing text line");
    if (n > 0 && text[n - 1] == '\r')
        --n;
    text[n] = '\0';
}

static inline void lab_finish(void)
{
    int ch;
    while ((ch = getchar()) != EOF)
        lab_require(isspace((unsigned char)ch), "unexpected extra input");
    lab_require(!ferror(stdin), "input read failed");
}

static inline int lab_array(long long values[LAB_CAP], int minimum)
{
    int n = lab_int(minimum, LAB_CAP);
    for (int i = 0; i < n; ++i)
        values[i] = lab_integer(-1000000, 1000000);
    return n;
}

static inline void lab_print_array(const long long values[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%s%lld", i ? " " : "", values[i]);
    putchar('\n');
}

static inline int lab_sorted(const long long values[], int n)
{
    for (int i = 1; i < n; ++i)
        if (values[i] < values[i - 1])
            return 0;
    return 1;
}

static inline int lab_prime(long long n)
{
    if (n < 2)
        return 0;
    for (long long d = 2; d <= n / d; ++d)
        if (n % d == 0)
            return 0;
    return 1;
}

static inline long long lab_gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

typedef struct
{
    int day, month, year;
} LabDate;
typedef struct
{
    int hour, minute, second;
} LabTime;
typedef struct
{
    int roll;
    char name[LAB_TEXT];
    double mark;
} LabStudent;

static inline LabDate lab_date(void)
{
    LabDate d;
    d.day = lab_int(1, 31);
    d.month = lab_int(1, 12);
    d.year = lab_int(1, 9999);
    return d;
}

static inline int lab_valid_date(LabDate d)
{
    static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap = d.year % 400 == 0 || (d.year % 4 == 0 && d.year % 100 != 0);
    return d.day <= days[d.month] + (d.month == 2 && leap);
}

static inline long lab_date_key(LabDate d)
{
    return (long)d.year * 10000 + d.month * 100 + d.day;
}

static inline LabTime lab_time(void)
{
    LabTime t;
    t.hour = lab_int(0, 23);
    t.minute = lab_int(0, 59);
    t.second = lab_int(0, 59);
    return t;
}

static inline int lab_seconds(LabTime t)
{
    return t.hour * 3600 + t.minute * 60 + t.second;
}

static inline LabStudent lab_student(void)
{
    LabStudent s = {0};
    s.roll = lab_int(1, 1000000);
    lab_line(s.name);
    lab_require(s.name[0] != '\0', "name cannot be empty");
    s.mark = lab_real(0, 100);
    return s;
}

static inline void lab_print_student(const LabStudent *s)
{
    printf("%d | %s | %.2f\n", s->roll, s->name, s->mark);
}

static inline void lab_students(LabStudent students[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        students[i] = lab_student();
        for (int j = 0; j < i; ++j)
            lab_require(students[i].roll != students[j].roll, "duplicate roll number");
    }
}

static inline void lab_close(FILE *file)
{
    lab_require(fclose(file) == 0, "file close failed");
}
#endif
