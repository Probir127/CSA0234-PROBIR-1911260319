/* Experiment 35: Largest and Smallest Using the Ternary Operator
 * Input: Three integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    int a = lab_int(-1000000, 1000000), b = lab_int(-1000000, 1000000),
        c = lab_int(-1000000, 1000000);
    int maximum = a > b ? (a > c ? a : c) : (b > c ? b : c),
        minimum = a < b ? (a < c ? a : c) : (b < c ? b : c);
    printf("Largest: %d\nSmallest: %d\n", maximum, minimum);
    lab_finish();
    return EXIT_SUCCESS;
}
