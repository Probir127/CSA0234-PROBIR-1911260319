/* Experiment 6: Area and Circumference of a Circle Using define
 * Input: Radius, 0..1000000.
 */
#include "lab.h"
#define PI 3.14159265358979323846

int main(void)
{
    double r = lab_real(0, 1000000);
    printf("Area: %.2f\nCircumference: %.2f\n", PI * r * r, 2 * PI * r);
    lab_finish();
    return EXIT_SUCCESS;
}
