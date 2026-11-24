/* Experiment 98: Call by Value vs Call by Reference Swap
 * Input: Two integers +/-1000000. C always passes values; copied pointers can identify caller
 * objects.
 */
#include "lab.h"
static void swap_values(long long a, long long b)
{
    long long t = a;
    a = b;
    b = t;
    printf("Inside value call: %lld %lld\n", a, b);
}
static void swap_pointers(long long *a, long long *b)
{
    long long t = *a;
    *a = *b;
    *b = t;
}

int main(void)
{
    long long a = lab_integer(-1000000, 1000000), b = lab_integer(-1000000, 1000000);
    swap_values(a, b);
    printf("After value call: %lld %lld\n", a, b);
    swap_pointers(&a, &b);
    printf("After pointer call: %lld %lld\n", a, b);
    lab_finish();
    return EXIT_SUCCESS;
}
