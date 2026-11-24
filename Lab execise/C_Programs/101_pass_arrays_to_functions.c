/* Experiment 101: Pass Arrays to Functions
 * Input: Count 1..100 and integers +/-1000000.
 */
#include "lab.h"
static long long sum_array(const long long values[], int n)
{
    long long sum = 0;
    for (int i = 0; i < n; ++i)
        sum += values[i];
    return sum;
}

int main(void)
{
    long long values[LAB_CAP];
    int n = lab_array(values, 1);
    long long sum = sum_array(values, n);
    printf("Sum: %lld\nMean: %.2f\n", sum, (double)sum / n);
    lab_finish();
    return EXIT_SUCCESS;
}
