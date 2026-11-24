/* Experiment 38: Fibonacci Series
 * Input: Term count 0..93, starting 0 1.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(0, 93);
    unsigned long long a = 0, b = 1;
    for (int i = 0; i < n; ++i)
    {
        printf("%s%llu", i ? " " : "", a);
        if (i + 1 < n)
        {
            unsigned long long next = a + b;
            a = b;
            b = next;
        }
    }
    putchar('\n');
    lab_finish();
    return EXIT_SUCCESS;
}
