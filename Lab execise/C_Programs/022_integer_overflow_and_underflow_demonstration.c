/* Experiment 22: Integer Overflow and Underflow Demonstration
 * Input: No input; unsigned wrap is defined, signed overflow is prevented.
 */
#include "lab.h"

int main(void)
{
    unsigned int maximum = UINT_MAX, zero = 0;
    printf("Unsigned overflow: %u\nUnsigned underflow: %u\n", maximum + 1U, zero - 1U);
    int largest = INT_MAX, smallest = INT_MIN;
    if (largest == INT_MAX && smallest == INT_MIN)
        puts("Signed overflow/underflow avoided: adding to INT_MAX or subtracting from INT_MIN is "
             "undefined.");
    lab_finish();
    return EXIT_SUCCESS;
}
