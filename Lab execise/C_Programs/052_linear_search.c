/* Experiment 52: Linear Search
 * Input: Count 0..100, then that many integers -1000000..1000000. Then target; returns first
 * zero-based index or -1.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0), index = -1;
    long long target = lab_integer(-1000000, 1000000);
    for (int i = 0; i < n; ++i)
        if (a[i] == target)
        {
            index = i;
            break;
        }
    printf("Index: %d\n", index);
    lab_finish();
    return EXIT_SUCCESS;
}
