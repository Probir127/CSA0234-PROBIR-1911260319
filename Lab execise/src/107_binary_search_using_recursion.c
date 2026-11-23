/* Experiment 107: Binary Search Using Recursion
 * Input: Count 0..100, nondecreasing integers +/-1000000, then target; any matching zero-based
 * index or -1.
 */
#include "lab.h"
static int search(const long long a[], int low, int high, long long target)
{
    if (low > high)
        return -1;
    int middle = low + (high - low) / 2;
    if (a[middle] == target)
        return middle;
    if (a[middle] < target)
        return search(a, middle + 1, high, target);
    return search(a, low, middle - 1, target);
}

int main(void)
{
    long long values[LAB_CAP];
    int n = lab_array(values, 0);
    lab_require(lab_sorted(values, n), "array must be sorted");
    long long target = lab_integer(-1000000, 1000000);
    printf("Index: %d\n", search(values, 0, n - 1, target));
    lab_finish();
    return EXIT_SUCCESS;
}
