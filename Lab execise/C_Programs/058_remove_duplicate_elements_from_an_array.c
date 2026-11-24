/* Experiment 58: Remove Duplicate Elements from an Array
 * Input: Count 0..100, then that many integers -1000000..1000000. Preserve first-occurrence order.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0), unique = 0;
    for (int i = 0; i < n; ++i)
    {
        int seen = 0;
        for (int j = 0; j < unique; ++j)
            if (a[j] == a[i])
                seen = 1;
        if (!seen)
            a[unique++] = a[i];
    }
    lab_print_array(a, unique);
    lab_finish();
    return EXIT_SUCCESS;
}
