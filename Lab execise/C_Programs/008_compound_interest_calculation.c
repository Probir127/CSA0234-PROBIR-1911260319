/* Experiment 8: Compound Interest Calculation
 * Input: Principal 0..1000000, annual percentage 0..100, whole years 0..100; annual compounding.
 */
#include "lab.h"

int main(void)
{
    double p = lab_real(0, 1000000), r = lab_real(0, 100);
    int t = lab_int(0, 100);
    double amount = p * pow(1 + r / 100, t);
    printf("Interest: %.2f\nAmount: %.2f\n", amount - p, amount);
    lab_finish();
    return EXIT_SUCCESS;
}
