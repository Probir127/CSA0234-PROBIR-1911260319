/* Experiment 14: Macros with Arguments Square and Maximum
 * Input: Two integers -1000000..1000000; pass side-effect-free arguments.
 */
#include "lab.h"
#define SQUARE(x) ((x) * (x))
#define MAXIMUM(a, b) ((a) > (b) ? (a) : (b))

int main(void)
{
    long long a = lab_integer(-1000000, 1000000), b = lab_integer(-1000000, 1000000);
    printf("Square: %lld\nMaximum: %lld\n", SQUARE(a), MAXIMUM(a, b));
    lab_finish();
    return EXIT_SUCCESS;
}
