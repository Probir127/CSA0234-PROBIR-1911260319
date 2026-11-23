/* Experiment 33: Roots of a Quadratic Equation
 * Input: a b c each -1000000..1000000; a must be nonzero; supports complex roots.
 */
#include "lab.h"

int main(void)
{
    double a = lab_real(-1000000, 1000000), b = lab_real(-1000000, 1000000),
           c = lab_real(-1000000, 1000000);
    lab_require(a != 0, "a must be nonzero");
    double d = b * b - 4 * a * c;
    if (d >= 0)
        printf("Roots: %.2f %.2f\n", (-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a));
    else
        printf("Roots: %.2f + %.2fi, %.2f - %.2fi\n", -b / (2 * a), sqrt(-d) / (2 * fabs(a)),
               -b / (2 * a), sqrt(-d) / (2 * fabs(a)));
    lab_finish();
    return EXIT_SUCCESS;
}
