/* Experiment 104: GCD Using Recursion
 * Input: Two integers 0..1000000000; gcd(0,0)=0.
 */
#include "lab.h"
static long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main(void)
{
    long long a = lab_integer(0, 1000000000), b = lab_integer(0, 1000000000);
    printf("GCD: %lld\n", gcd(a, b));
    lab_finish();
    return EXIT_SUCCESS;
}
