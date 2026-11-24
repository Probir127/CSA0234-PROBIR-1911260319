/* Experiment 2: Display Size and Range of All Primitive Data Types
 * Input: No input.
 */
#include "lab.h"

int main(void)
{
    printf("char: size=%zu range=%d..%d\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("signed char: size=%zu range=%d..%d\n", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: size=%zu range=0..%u\n", sizeof(unsigned char), (unsigned)UCHAR_MAX);
    printf("short: size=%zu range=%d..%d\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned short: size=%zu range=0..%u\n", sizeof(unsigned short), (unsigned)USHRT_MAX);
    printf("int: size=%zu range=%d..%d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int: size=%zu range=0..%u\n", sizeof(unsigned int), UINT_MAX);
    printf("long: size=%zu range=%ld..%ld\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("unsigned long: size=%zu range=0..%lu\n", sizeof(unsigned long), ULONG_MAX);
    printf("long long: size=%zu range=%lld..%lld\n", sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("unsigned long long: size=%zu range=0..%llu\n", sizeof(unsigned long long), ULLONG_MAX);
    printf("float: size=%zu lowest=%g min-positive-normal=%g max=%g\n", sizeof(float),
           -(double)FLT_MAX, (double)FLT_MIN, (double)FLT_MAX);
    printf("double: size=%zu lowest=%g min-positive-normal=%g max=%g\n", sizeof(double), -DBL_MAX,
           DBL_MIN, DBL_MAX);
    printf("long double: size=%zu lowest=%Lg min-positive-normal=%Lg max=%Lg\n",
           sizeof(long double), -LDBL_MAX, LDBL_MIN, LDBL_MAX);
    printf("_Bool: size=%zu range=0..1\n", sizeof(_Bool));
    puts("void has no object size or value range. Floating ranges include negative values and "
         "zero; minimum shown is positive and normal.");
    lab_finish();
    return EXIT_SUCCESS;
}
