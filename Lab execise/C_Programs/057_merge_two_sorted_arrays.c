/* Experiment 57: Merge Two Sorted Arrays
 * Input: First count and sorted array, then second count and sorted array; each count 0..100,
 * values +/-1000000.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP], b[LAB_CAP], merged[2 * LAB_CAP];
    int n = lab_array(a, 0), m = lab_array(b, 0);
    lab_require(lab_sorted(a, n) && lab_sorted(b, m), "arrays must be sorted");
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
        merged[k++] = a[i] <= b[j] ? a[i++] : b[j++];
    while (i < n)
        merged[k++] = a[i++];
    while (j < m)
        merged[k++] = b[j++];
    lab_print_array(merged, k);
    lab_finish();
    return EXIT_SUCCESS;
}
