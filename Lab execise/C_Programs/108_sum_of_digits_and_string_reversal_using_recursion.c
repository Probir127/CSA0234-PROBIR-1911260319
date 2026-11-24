/* Experiment 108: Sum of Digits and String Reversal Using Recursion
 * Input: Nonnegative integer 0..1000000000000 on its own line, then a text line up to 255 bytes.
 */
#include "lab.h"
static long long digit_sum(long long n)
{
    return n < 10 ? n : n % 10 + digit_sum(n / 10);
}
static void reverse(const char *text)
{
    if (*text)
    {
        reverse(text + 1);
        putchar((unsigned char)*text);
    }
}

int main(void)
{
    long long n = lab_integer(0, 1000000000000LL);
    char text[LAB_TEXT];
    lab_line(text);
    printf("Digit sum: %lld\nReversed: ", digit_sum(n));
    reverse(text);
    putchar('\n');
    lab_finish();
    return EXIT_SUCCESS;
}
