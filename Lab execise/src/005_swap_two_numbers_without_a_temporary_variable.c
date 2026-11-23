/* Experiment 5: Swap Two Numbers Without a Temporary Variable
 * Input: Two unsigned integers, 0..UINT_MAX; XOR swap.
 */
#include "lab.h"

int main(void)
{
    unsigned int a = (unsigned int)lab_integer(0, UINT_MAX),
                 b = (unsigned int)lab_integer(0, UINT_MAX);
    a ^= b;
    b ^= a;
    a ^= b;
    printf("%u %u\n", a, b);
    lab_finish();
    return EXIT_SUCCESS;
}
