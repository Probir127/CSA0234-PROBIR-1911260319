/* Experiment 36: Sum of the First N Natural Numbers
 * Input: N 0..1000000.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(0, 1000000);
    long long sum = 0;
    for (int i = 1; i <= n; ++i)
        sum += i;
    printf("Sum: %lld\n", sum);
    lab_finish();
    return EXIT_SUCCESS;
}
