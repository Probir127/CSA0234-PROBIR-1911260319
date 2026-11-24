/* Experiment 93: Structure with Bit Fields
 * Input: Ready 0..1, mode 0..3, count 0..31; bit allocation and layout are implementation-defined.
 */
#include "lab.h"
struct Flags
{
    unsigned ready : 1;
    unsigned mode : 2;
    unsigned count : 5;
};

int main(void)
{
    struct Flags flags;
    flags.ready = (unsigned)lab_int(0, 1);
    flags.mode = (unsigned)lab_int(0, 3);
    flags.count = (unsigned)lab_int(0, 31);
    printf("Ready: %u\nMode: %u\nCount: %u\n", (unsigned)flags.ready, (unsigned)flags.mode,
           (unsigned)flags.count);
    lab_finish();
    return EXIT_SUCCESS;
}
