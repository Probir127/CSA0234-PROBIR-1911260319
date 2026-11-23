/* Experiment 28: Even or Odd Using Modulus and Bitwise AND
 * Input: Integer -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(-1000000, 1000000);
    printf("Modulus: %s\nBitwise: %s\n", n % 2 == 0 ? "Even" : "Odd",
           ((unsigned)n & 1U) ? "Odd" : "Even");
    lab_finish();
    return EXIT_SUCCESS;
}
