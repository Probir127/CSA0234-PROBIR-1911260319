/* Experiment 62: Row wise and Column wise Sum of a Matrix
 * Input: Rows and columns 1..10, then matrix row-major; entries +/-10000.
 */
#include "lab.h"
static void read_matrix(long long a[10][10], int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            a[i][j] = lab_integer(-10000, 10000);
}

int main(void)
{
    int r = lab_int(1, 10), c = lab_int(1, 10);
    long long a[10][10], rows[10] = {0}, columns[10] = {0};
    read_matrix(a, r, c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
        {
            rows[i] += a[i][j];
            columns[j] += a[i][j];
        }
    printf("Rows: ");
    lab_print_array(rows, r);
    printf("Columns: ");
    lab_print_array(columns, c);
    lab_finish();
    return EXIT_SUCCESS;
}
