/* Experiment 16: Area of a Triangle Using Heron Formula
 * Input: Three positive side lengths, at most 1000000, satisfying the strict triangle inequality.
 */
#include "lab.h"

int main(void)
{
    double a = lab_real(0, 1000000), b = lab_real(0, 1000000), c = lab_real(0, 1000000);
    lab_require(a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a, "invalid triangle");
    double s = (a + b + c) / 2;
    printf("Area: %.2f\n", sqrt(fmax(0, s * (s - a) * (s - b) * (s - c))));
    lab_finish();
    return EXIT_SUCCESS;
}
