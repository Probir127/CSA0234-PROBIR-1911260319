/* Experiment 63: Diagonal Sums and Symmetric Matrix Check
 * Input: Square size 1..10, then matrix row-major; entries +/-10000. Both diagonals include their
 * centre.
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
    int n = lab_int(1, 10), symmetric = 1;
    long long a[10][10], main_sum = 0, secondary = 0;
    read_matrix(a, n, n);
    for (int i = 0; i < n; ++i)
    {
        main_sum += a[i][i];
        secondary += a[i][n - 1 - i];
        for (int j = i + 1; j < n; ++j)
            if (a[i][j] != a[j][i])
                symmetric = 0;
    }
    printf("Main diagonal: %lld\nSecondary diagonal: %lld\n%s\n", main_sum, secondary,
           symmetric ? "Symmetric" : "Not symmetric");
    lab_finish();
    return EXIT_SUCCESS;
}
