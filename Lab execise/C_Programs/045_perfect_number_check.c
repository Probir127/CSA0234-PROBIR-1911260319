/* Experiment 45: Perfect Number Check
 * Input: Integer 1..1000000000; compare with the sum of proper positive divisors.
 */
#include "lab.h"

int main(void)
{
    long long n = lab_integer(1, 1000000000), sum = n > 1 ? 1 : 0;
    for (long long d = 2; d <= n / d; ++d)
        if (n % d == 0)
        {
            sum += d;
            if (d != n / d)
                sum += n / d;
        }
    puts(sum == n ? "Perfect" : "Not perfect");
    lab_finish();
    return EXIT_SUCCESS;
}
