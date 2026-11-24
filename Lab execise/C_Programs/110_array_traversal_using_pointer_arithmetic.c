/* Experiment 110: Array Traversal Using Pointer Arithmetic
 * Input: Count 0..100 and integers +/-1000000.
 */
#include "lab.h"

int main(void)
{
    long long values[LAB_CAP];
    int n = lab_array(values, 0);
    for (long long *p = values; p < values + n; ++p)
        printf("%s%lld", p == values ? "" : " ", *p);
    putchar('\n');
    lab_finish();
    return EXIT_SUCCESS;
}
