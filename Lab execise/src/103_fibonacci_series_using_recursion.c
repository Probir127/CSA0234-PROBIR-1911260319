/* Experiment 103: Fibonacci Series Using Recursion
 * Input: Term count 0..93, starting 0 1. Recursive memoization avoids exponential work.
 */
#include "lab.h"
static unsigned long long fibonacci(int n, unsigned long long memo[], int known[])
{
    if (n < 2)
        return (unsigned)n;
    if (!known[n])
    {
        memo[n] = fibonacci(n - 1, memo, known) + fibonacci(n - 2, memo, known);
        known[n] = 1;
    }
    return memo[n];
}

int main(void)
{
    int n = lab_int(0, 93), known[93] = {0};
    unsigned long long memo[93] = {0};
    for (int i = 0; i < n; ++i)
        printf("%s%llu", i ? " " : "", fibonacci(i, memo, known));
    putchar('\n');
    lab_finish();
    return EXIT_SUCCESS;
}
