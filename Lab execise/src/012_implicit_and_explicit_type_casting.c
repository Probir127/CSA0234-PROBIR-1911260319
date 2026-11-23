/* Experiment 12: Implicit and Explicit Type Casting
 * Input: Integer -1000000..1000000, real -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(-1000000, 1000000);
    double x = lab_real(-1000000, 1000000), implicit = n;
    printf("Implicit double: %.2f\nExplicit integer: %d\nInteger division: %d\nFloating division: "
           "%.2f\n",
           implicit, (int)x, n / 2, (double)n / 2);
    lab_finish();
    return EXIT_SUCCESS;
}
