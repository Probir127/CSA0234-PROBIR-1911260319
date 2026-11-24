/* Experiment 25: Arithmetic Operators Demonstration
 * Input: Two integers -1000000..1000000; second must be nonzero.
 */
#include "lab.h"

int main(void)
{
    long long a = lab_integer(-1000000, 1000000), b = lab_integer(-1000000, 1000000);
    lab_require(b != 0, "division by zero");
    printf("Add: %lld\nSubtract: %lld\nMultiply: %lld\nDivide: %lld\nRemainder: %lld\n", a + b,
           a - b, a * b, a / b, a % b);
    lab_finish();
    return EXIT_SUCCESS;
}
