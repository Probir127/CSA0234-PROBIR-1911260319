/* Experiment 21: Formatted Output Using printf Width and Precision
 * Input: One real -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    double x = lab_real(-1000000, 1000000);
    printf("Right: [%10.2f]\nLeft:  [%-10.2f]\nPrecise: %.4f\n", x, x, x);
    lab_finish();
    return EXIT_SUCCESS;
}
