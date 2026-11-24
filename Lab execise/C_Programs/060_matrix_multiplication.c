/* Experiment 60: Matrix Multiplication
 * Input: r k c (1..10), then A (r by k), B (k by c); entries +/-10000.
 */
#include "lab.h"
static void read_matrix(long long a[10][10], int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            a[i][j] = lab_integer(-10000, 10000);
}

static void print_matrix(long long a[10][10], int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
            printf("%s%lld", j ? " " : "", a[i][j]);
        putchar('\n');
    }
}

int main(void)
{
    int r = lab_int(1, 10), k = lab_int(1, 10), c = lab_int(1, 10);
    long long a[10][10], b[10][10], product[10][10] = {0};
    read_matrix(a, r, k);
    read_matrix(b, k, c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            for (int t = 0; t < k; ++t)
                product[i][j] += a[i][t] * b[t][j];
    print_matrix(product, r, c);
    lab_finish();
    return EXIT_SUCCESS;
}
