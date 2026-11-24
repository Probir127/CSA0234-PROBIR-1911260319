/* Experiment 46: Star Pyramid and Diamond Patterns
 * Input: Row count 1..10.
 */
#include "lab.h"
static void star_row(int n, int i)
{
    for (int j = 0; j < n - i; ++j)
        putchar(' ');
    for (int j = 0; j < 2 * i - 1; ++j)
        putchar('*');
    putchar('\n');
}

int main(void)
{
    int n = lab_int(1, 10);
    puts("Pyramid:");
    for (int i = 1; i <= n; ++i)
        star_row(n, i);
    puts("Diamond:");
    for (int i = 1; i <= n; ++i)
        star_row(n, i);
    for (int i = n - 1; i >= 1; --i)
        star_row(n, i);
    lab_finish();
    return EXIT_SUCCESS;
}
