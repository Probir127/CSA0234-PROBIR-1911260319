/* Experiment 43: Reverse a Number
 * Input: Integer -1000000000..1000000000; preserve its sign.
 */
#include "lab.h"

int main(void)
{
    long long n = lab_integer(-1000000000, 1000000000), copy = n < 0 ? -n : n, reversed = 0;
    do
    {
        reversed = reversed * 10 + copy % 10;
        copy /= 10;
    } while (copy);
    printf("Reversed: %lld\n", n < 0 ? -reversed : reversed);
    lab_finish();
    return EXIT_SUCCESS;
}
