/* Experiment 76: Distance Between Two Points Using Structures
 * Input: x1 y1 x2 y2, each +/-1000000.
 */
#include "lab.h"
typedef struct
{
    double x, y;
} Point;

int main(void)
{
    Point a = {lab_real(-1000000, 1000000), lab_real(-1000000, 1000000)},
          b = {lab_real(-1000000, 1000000), lab_real(-1000000, 1000000)};
    printf("Distance: %.2f\n", hypot(b.x - a.x, b.y - a.y));
    lab_finish();
    return EXIT_SUCCESS;
}
