/* Experiment 29: Largest of Three Numbers Using if else
 * Input: Three integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    int a = lab_int(-1000000, 1000000), b = lab_int(-1000000, 1000000),
        c = lab_int(-1000000, 1000000), largest;
    if (a >= b && a >= c)
        largest = a;
    else if (b >= c)
        largest = b;
    else
        largest = c;
    printf("Largest: %d\n", largest);
    lab_finish();
    return EXIT_SUCCESS;
}
