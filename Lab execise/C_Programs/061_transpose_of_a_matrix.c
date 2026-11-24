/* Experiment 61: Transpose of a Matrix
 * Input: Rows and columns 1..10, then the matrix row-major; entries +/-10000.
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
    int r = lab_int(1, 10), c = lab_int(1, 10);
    long long a[10][10], transpose[10][10];
    read_matrix(a, r, c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            transpose[j][i] = a[i][j];
    print_matrix(transpose, c, r);
    lab_finish();
    return EXIT_SUCCESS;
}
