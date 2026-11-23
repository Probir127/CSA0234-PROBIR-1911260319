#include "input.h"

/* Return any matching zero-based index, or -1 if no match exists. */
static int binary_search(const int values[], int n, int target)
{
    int low = 0, high = n - 1;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (values[middle] == target) return middle;
        if (values[middle] < target) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}

int main(void)
{
    int n, values[100], target;
    if (!read_int(&n, 0, 100)) return input_error();
    for (int i = 0; i < n; ++i) {
        if (!read_int(&values[i], INT_MIN, INT_MAX)) return input_error();
        if (i > 0 && values[i] < values[i - 1]) return input_error();
    }
    if (!read_int(&target, INT_MIN, INT_MAX) || !input_finished()) return input_error();
    printf("Index: %d\n", binary_search(values, n, target));
    return EXIT_SUCCESS;
}
