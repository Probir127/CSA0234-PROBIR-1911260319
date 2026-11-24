/* Experiment 19: Extract the Digits of a Three Digit Number
 * Input: Integer 100..999.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(100, 999);
    printf("Hundreds: %d\nTens: %d\nUnits: %d\n", n / 100, n / 10 % 10, n % 10);
    lab_finish();
    return EXIT_SUCCESS;
}
