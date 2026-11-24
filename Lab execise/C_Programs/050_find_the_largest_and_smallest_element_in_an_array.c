/* Experiment 50: Find the Largest and Smallest Element in an Array
 * Input: Count 1..100, then that many integers -1000001..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 1);
    long long minimum = a[0], maximum = a[0];
    for (int i = 1; i < n; ++i)
    {
        if (a[i] < minimum)
            minimum = a[i];
        if (a[i] > maximum)
            maximum = a[i];
    }
    printf("Largest: %lld\nSmallest: %lld\n", maximum, minimum);
    lab_finish();
    return EXIT_SUCCESS;
}
