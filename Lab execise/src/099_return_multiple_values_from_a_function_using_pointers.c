/* Experiment 99: Return Multiple Values from a Function Using Pointers
 * Input: Two integers +/-1000000.
 */
#include "lab.h"
static void calculate(long long a, long long b, long long *sum, long long *difference,
                      long long *product)
{
    *sum = a + b;
    *difference = a - b;
    *product = a * b;
}

int main(void)
{
    long long a = lab_integer(-1000000, 1000000), b = lab_integer(-1000000, 1000000), sum,
              difference, product;
    calculate(a, b, &sum, &difference, &product);
    printf("Sum: %lld\nDifference: %lld\nProduct: %lld\n", sum, difference, product);
    lab_finish();
    return EXIT_SUCCESS;
}
