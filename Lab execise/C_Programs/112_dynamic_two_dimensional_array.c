/* Experiment 112: Dynamic Two Dimensional Array
 * Input: Rows and columns 1..10, then row-major integers +/-1000000.
 */
#include "lab.h"

int main(void)
{
    int rows = lab_int(1, 10), columns = lab_int(1, 10);
    long long **matrix = calloc((size_t)rows, sizeof *matrix);
    lab_require(matrix != NULL, "allocation failed");
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = calloc((size_t)columns, sizeof *matrix[i]);
        if (!matrix[i])
        {
            for (int j = 0; j < i; ++j)
                free(matrix[j]);
            free(matrix);
            lab_require(0, "row allocation failed");
        }
    }
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            matrix[i][j] = lab_integer(-1000000, 1000000);
    for (int i = 0; i < rows; ++i)
    {
        lab_print_array(matrix[i], columns);
        free(matrix[i]);
    }
    free(matrix);
    lab_finish();
    return EXIT_SUCCESS;
}
