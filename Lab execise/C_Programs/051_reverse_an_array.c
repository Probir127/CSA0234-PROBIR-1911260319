/* Experiment 51: Reverse an Array
 * Input: Count 0..100, then that many integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0);
    for (int i = 0; i < n / 2; ++i)
    {
        long long temporary = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = temporary;
    }
    lab_print_array(a, n);
    lab_finish();
    return EXIT_SUCCESS;
}
