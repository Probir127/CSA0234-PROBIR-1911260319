/* Experiment 106: Power of a Number Using Recursion
 * Input: Base -100..100, integer exponent -100..100. Zero to a negative power is invalid; 0^0 is
 * defined as 1 in this exercise.
 */
#include "lab.h"
static double power(double base, unsigned exponent)
{
    if (exponent == 0)
        return 1;
    double half = power(base, exponent / 2);
    return exponent % 2 ? half * half * base : half * half;
}

int main(void)
{
    double base = lab_real(-100, 100);
    int exponent = lab_int(-100, 100);
    lab_require(base != 0 || exponent >= 0, "zero to negative power");
    double result = power(base, (unsigned)(exponent < 0 ? -exponent : exponent));
    if (exponent < 0)
        result = 1 / result;
    lab_require(isfinite(result) && (result != 0 || base == 0),
                "result outside floating-point range");
    printf("Power: %.6f\n", result);
    lab_finish();
    return EXIT_SUCCESS;
}
