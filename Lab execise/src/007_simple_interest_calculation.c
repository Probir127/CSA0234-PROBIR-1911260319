/* Experiment 7: Simple Interest Calculation
 * Input: Principal, annual percentage rate, years; each 0..1000000.
 */
#include "lab.h"

int main(void)
{
    double p = lab_real(0, 1000000), r = lab_real(0, 1000000), t = lab_real(0, 1000000);
    double interest = p * r * t / 100;
    printf("Interest: %.2f\nAmount: %.2f\n", interest, p + interest);
    lab_finish();
    return EXIT_SUCCESS;
}
