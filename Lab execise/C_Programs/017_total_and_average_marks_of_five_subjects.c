/* Experiment 17: Total and Average Marks of Five Subjects
 * Input: Five marks, each 0..100.
 */
#include "lab.h"

int main(void)
{
    double total = 0;
    for (int i = 0; i < 5; ++i)
        total += lab_real(0, 100);
    printf("Total: %.2f\nAverage: %.2f\n", total, total / 5);
    lab_finish();
    return EXIT_SUCCESS;
}
