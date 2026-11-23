/* Experiment 18: Convert Seconds to HH MM SS
 * Input: Seconds 0..1000000000; hours may exceed 23.
 */
#include "lab.h"

int main(void)
{
    long long n = lab_integer(0, 1000000000);
    printf("%02lld:%02lld:%02lld\n", n / 3600, n % 3600 / 60, n % 60);
    lab_finish();
    return EXIT_SUCCESS;
}
