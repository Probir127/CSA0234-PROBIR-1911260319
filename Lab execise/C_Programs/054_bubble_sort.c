/* Experiment 54: Bubble Sort
 * Input: Count 0..100, then that many integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0);
    for (int end = n - 1; end > 0; --end)
    {
        int changed = 0;
        for (int j = 0; j < end; ++j)
            if (a[j] > a[j + 1])
            {
                long long t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                changed = 1;
            }
        if (!changed)
            break;
    }
    lab_print_array(a, n);
    lab_finish();
    return EXIT_SUCCESS;
}
