/* Experiment 102: Factorial Using Recursion
 * Input: N 0..20.
 */
#include "lab.h"
static unsigned long long factorial(unsigned n)
{
    return n < 2 ? 1 : (unsigned long long)n * factorial(n - 1);
}

int main(void)
{
    unsigned n = (unsigned)lab_int(0, 20);
    printf("Factorial: %llu\n", factorial(n));
    lab_finish();
    return EXIT_SUCCESS;
}
