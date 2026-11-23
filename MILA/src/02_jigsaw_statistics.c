#include "input.h"

static int read_values(int values[], int n)
{
    for (int i = 0; i < n; ++i)
        if (!read_int(&values[i], INT_MIN, INT_MAX)) return 0;
    return input_finished();
}

static int minimum(const int values[], int n)
{
    int result = values[0];
    for (int i = 1; i < n; ++i)
        if (values[i] < result) result = values[i];
    return result;
}

static int maximum(const int values[], int n)
{
    int result = values[0];
    for (int i = 1; i < n; ++i)
        if (values[i] > result) result = values[i];
    return result;
}

static long long total(const int values[], int n)
{
    long long result = 0;
    for (int i = 0; i < n; ++i) result += values[i];
    return result;
}

int main(void)
{
    int n, values[100];
    if (!read_int(&n, 1, 100) || !read_values(values, n)) return input_error();
    long long sum = total(values, n);
    printf("Min: %d\nMax: %d\nSum: %lld\nMean: %.2f\n",
           minimum(values, n), maximum(values, n), sum, (double)sum / n);
    return EXIT_SUCCESS;
}
