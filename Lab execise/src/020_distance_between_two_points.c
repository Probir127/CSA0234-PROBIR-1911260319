/* Experiment 20: Distance Between Two Points
 * Input: x1 y1 x2 y2, each -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    double x1 = lab_real(-1000000, 1000000), y1 = lab_real(-1000000, 1000000),
           x2 = lab_real(-1000000, 1000000), y2 = lab_real(-1000000, 1000000);
    printf("Distance: %.2f\n", hypot(x2 - x1, y2 - y1));
    lab_finish();
    return EXIT_SUCCESS;
}
