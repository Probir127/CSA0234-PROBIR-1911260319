/* Experiment 100: Modular Prime Number Program Using Functions
 * Input: Integer +/-1000000000.
 */
#include "lab.h"
static int is_prime(long long n)
{
    if (n < 2)
        return 0;
    for (long long divisor = 2; divisor <= n / divisor; ++divisor)
        if (n % divisor == 0)
            return 0;
    return 1;
}

int main(void)
{
    long long n = lab_integer(-1000000000, 1000000000);
    puts(is_prime(n) ? "Prime" : "Not prime");
    lab_finish();
    return EXIT_SUCCESS;
}
