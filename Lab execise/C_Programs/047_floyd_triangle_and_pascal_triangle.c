/* Experiment 47: Floyd Triangle and Pascal Triangle
 * Input: Row count 1..10.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(1, 10), value = 1;
    puts("Floyd:");
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
            printf("%s%d", j ? " " : "", value++);
        putchar('\n');
    }
    puts("Pascal:");
    for (int i = 0; i < n; ++i)
    {
        long long c = 1;
        for (int j = 0; j <= i; ++j)
        {
            printf("%s%lld", j ? " " : "", c);
            c = c * (i - j) / (j + 1);
        }
        putchar('\n');
    }
    lab_finish();
    return EXIT_SUCCESS;
}
