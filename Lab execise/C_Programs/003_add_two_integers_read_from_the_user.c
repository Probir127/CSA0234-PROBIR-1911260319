/* Experiment 3: Add Two Integers Read from the User
 * Input: Two integers, each -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a = lab_integer(-1000000, 1000000), b = lab_integer(-1000000, 1000000);
    printf("Sum: %lld\n", a + b);
    lab_finish();
    return EXIT_SUCCESS;
}
