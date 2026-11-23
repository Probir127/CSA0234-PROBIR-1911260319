#include "input.h"

int main(void)
{
    int n, values[100];
    long long sum = 0;
    if (!read_int(&n, 1, 100)) return input_error();
    for (int i = 0; i < n; ++i) {
        if (!read_int(&values[i], INT_MIN, INT_MAX)) return input_error();
        sum += values[i];
    }
    if (!input_finished()) return input_error();
    printf("Sum: %lld\nMean: %.2f\n", sum, (double)sum / n);
    return EXIT_SUCCESS;
}
