/* Experiment 40: Prime Numbers in a Given Range
 * Input: Inclusive lower and upper endpoints, 0..100000; lower<=upper.
 */
#include "lab.h"

int main(void)
{
    int low = lab_int(0, 100000), high = lab_int(0, 100000);
    lab_require(low <= high, "reversed range");
    int printed = 0;
    for (int n = low; n <= high; ++n)
        if (lab_prime(n))
        {
            printf("%s%d", printed ? " " : "", n);
            printed = 1;
        }
    putchar('\n');
    lab_finish();
    return EXIT_SUCCESS;
}
