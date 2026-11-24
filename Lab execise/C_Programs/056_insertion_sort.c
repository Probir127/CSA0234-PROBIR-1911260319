/* Experiment 56: Insertion Sort
 * Input: Count 0..100, then that many integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0);
    for (int i = 1; i < n; ++i)
    {
        long long key = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > key)
        {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = key;
    }
    lab_print_array(a, n);
    lab_finish();
    return EXIT_SUCCESS;
}
