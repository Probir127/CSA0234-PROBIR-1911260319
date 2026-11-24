/* Experiment 53: Binary Search
 * Input: Count 0..100, then that many integers -1000000..1000000. Nondecreasing order required;
 * then target; returns any matching zero-based index or -1.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0);
    lab_require(lab_sorted(a, n), "array must be sorted");
    long long target = lab_integer(-1000000, 1000000);
    int low = 0, high = n - 1, index = -1;
    while (low <= high)
    {
        int middle = low + (high - low) / 2;
        if (a[middle] == target)
        {
            index = middle;
            break;
        }
        if (a[middle] < target)
            low = middle + 1;
        else
            high = middle - 1;
    }
    printf("Index: %d\n", index);
    lab_finish();
    return EXIT_SUCCESS;
}
