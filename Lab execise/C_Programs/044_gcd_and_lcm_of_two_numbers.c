/* Experiment 44: GCD and LCM of Two Numbers
 * Input: Two integers 0..1000000000; gcd(0,0)=0 and lcm with zero is 0.
 */
#include "lab.h"

int main(void)
{
    long long a = lab_integer(0, 1000000000), b = lab_integer(0, 1000000000), g = lab_gcd(a, b),
              l = (a == 0 || b == 0) ? 0 : (a / g) * b;
    printf("GCD: %lld\nLCM: %lld\n", g, l);
    lab_finish();
    return EXIT_SUCCESS;
}
