/* Experiment 39: Prime Number Check
 * Input: Integer -1000000000..1000000000.
 */
#include "lab.h"

int main(void)
{
    long long n = lab_integer(-1000000000, 1000000000);
    int prime = n >= 2;
    for (long long d = 2; prime && d <= n / d; ++d)
        if (n % d == 0)
            prime = 0;
    puts(prime ? "Prime" : "Not prime");
    lab_finish();
    return EXIT_SUCCESS;
}
