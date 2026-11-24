/* Experiment 27: Bitwise Operators Demonstration
 * Input: Two unsigned values 0..65535 and shift 0..15; NOT is explicitly masked to 16 bits.
 */
#include "lab.h"

int main(void)
{
    unsigned a = (unsigned)lab_int(0, 65535), b = (unsigned)lab_int(0, 65535);
    int shift = lab_int(0, 15);
    printf("AND: %u\nOR: %u\nXOR: %u\nNOT16: %u\nLeft: %u\nRight: %u\n", a & b, a | b, a ^ b,
           (~a) & 65535U, a << shift, a >> shift);
    lab_finish();
    return EXIT_SUCCESS;
}
