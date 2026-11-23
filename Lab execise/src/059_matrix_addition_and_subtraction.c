/* Experiment 59: Matrix Addition and Subtraction
 * Input: Rows and columns 1..10, then two matrices of that shape in row-major order; entries
 * +/-10000.
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
    long long a[10][10], b[10][10], sum[10][10], difference[10][10];
    read_matrix(a, r, c);
    read_matrix(b, r, c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
        {
            sum[i][j] = a[i][j] + b[i][j];
            difference[i][j] = a[i][j] - b[i][j];
        }
    puts("Addition:");
    print_matrix(sum, r, c);
    puts("Subtraction:");
    print_matrix(difference, r, c);
    lab_finish();
    return EXIT_SUCCESS;
}
