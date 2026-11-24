/* Experiment 37: Factorial of a Number Using Loops
 * Input: N 0..20.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(0, 20);
    unsigned long long value = 1;
    for (int i = 2; i <= n; ++i)
        value *= (unsigned)i;
    printf("Factorial: %llu\n", value);
    lab_finish();
    return EXIT_SUCCESS;
}
