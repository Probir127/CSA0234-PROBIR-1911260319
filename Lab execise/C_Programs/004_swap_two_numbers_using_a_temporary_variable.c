/* Experiment 4: Swap Two Numbers Using a Temporary Variable
 * Input: Two integers, each -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a = lab_integer(-1000000, 1000000), b = lab_integer(-1000000, 1000000);
    long long temporary = a;
    a = b;
    b = temporary;
    printf("%lld %lld\n", a, b);
    lab_finish();
    return EXIT_SUCCESS;
}
