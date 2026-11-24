/* Experiment 26: Relational and Logical Operators Demonstration
 * Input: Two integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    int a = lab_int(-1000000, 1000000), b = lab_int(-1000000, 1000000);
    printf("Equal: %d\nNot equal: %d\nLess: %d\nGreater: %d\nLess or equal: %d\nGreater or equal: "
           "%d\nAND: %d\nOR: %d\nNOT first: %d\n",
           a == b, a != b, a<b, a> b, a <= b, a >= b, a && b, a || b, !a);
    lab_finish();
    return EXIT_SUCCESS;
}
