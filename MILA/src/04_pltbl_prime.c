#include "input.h"

static int is_prime(int n)
{
    if (n < 2) return 0;
    for (int divisor = 2; divisor <= n / divisor; ++divisor)
        if (n % divisor == 0) return 0;
    return 1;
}

int main(void)
{
    int n;
    if (!read_int(&n, INT_MIN, INT_MAX) || !input_finished()) return input_error();
    printf("%d is %sprime\n", n, is_prime(n) ? "" : "not ");
    return EXIT_SUCCESS;
}
