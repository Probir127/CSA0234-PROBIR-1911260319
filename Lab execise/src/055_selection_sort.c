/* Experiment 55: Selection Sort
 * Input: Count 0..100, then that many integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0);
    for (int i = 0; i < n - 1; ++i)
    {
        int smallest = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[smallest])
                smallest = j;
        long long t = a[i];
        a[i] = a[smallest];
        a[smallest] = t;
    }
    lab_print_array(a, n);
    lab_finish();
    return EXIT_SUCCESS;
}
