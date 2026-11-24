/* Experiment 41: Armstrong Number
 * Input: Nonnegative integer 0..1000000000; sum each digit raised to the digit count.
 */
#include "lab.h"

int main(void)
{
    long long n = lab_integer(0, 1000000000), copy = n, sum = 0;
    int digits = 0;
    do
    {
        ++digits;
        copy /= 10;
    } while (copy);
    copy = n;
    do
    {
        int digit = (int)(copy % 10);
        long long power = 1;
        for (int i = 0; i < digits; ++i)
            power *= digit;
        sum += power;
        copy /= 10;
    } while (copy);
    puts(sum == n ? "Armstrong" : "Not Armstrong");
    lab_finish();
    return EXIT_SUCCESS;
}
