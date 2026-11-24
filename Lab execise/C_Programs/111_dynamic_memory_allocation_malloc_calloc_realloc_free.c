/* Experiment 111: Dynamic Memory Allocation malloc calloc realloc free
 * Input: Initial count 1..100 and integers +/-1000000, then added count 0..100 and added integers.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(1, 100);
    long long *values = malloc((size_t)n * sizeof *values),
              *zeros = calloc((size_t)n, sizeof *zeros);
    if (!values || !zeros)
    {
        free(values);
        free(zeros);
        lab_require(0, "allocation failed");
    }
    for (int i = 0; i < n; ++i)
        values[i] = lab_integer(-1000000, 1000000);
    printf("malloc: ");
    lab_print_array(values, n);
    printf("calloc first: %lld\n", zeros[0]);
    int m = lab_int(0, 100);
    long long *grown = realloc(values, (size_t)(n + m) * sizeof *values);
    if (!grown)
    {
        free(values);
        free(zeros);
        lab_require(0, "reallocation failed");
    }
    values = grown;
    for (int i = n; i < n + m; ++i)
        values[i] = lab_integer(-1000000, 1000000);
    printf("realloc: ");
    lab_print_array(values, n + m);
    free(values);
    free(zeros);
    lab_finish();
    return EXIT_SUCCESS;
}
