/* Experiment 13: Constants Using const and define
 * Input: Radius 0..1000000.
 */
#include "lab.h"
#define PI 3.14159265358979323846

int main(void)
{
    const double radius = lab_real(0, 1000000);
    printf("PI: %.6f\nRadius: %.2f\nArea: %.2f\n", PI, radius, PI * radius * radius);
    lab_finish();
    return EXIT_SUCCESS;
}
