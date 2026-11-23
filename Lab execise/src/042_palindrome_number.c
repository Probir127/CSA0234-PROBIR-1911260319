/* Experiment 42: Palindrome Number
 * Input: Integer 0..1000000000.
 */
#include "lab.h"

int main(void)
{
    long long n = lab_integer(0, 1000000000), copy = n, reversed = 0;
    do
    {
        reversed = reversed * 10 + copy % 10;
        copy /= 10;
    } while (copy);
    puts(reversed == n ? "Palindrome" : "Not palindrome");
    lab_finish();
    return EXIT_SUCCESS;
}
