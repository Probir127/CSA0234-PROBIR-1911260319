#include "input.h"

static void swap_copies(int a, int b)
{
    int temporary = a;
    a = b;
    b = temporary;
    printf("Inside value function: %d %d\n", a, b);
}

static void swap_pointed_values(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

int main(void)
{
    int a, b;
    if (!read_int(&a, INT_MIN, INT_MAX) || !read_int(&b, INT_MIN, INT_MAX) ||
        !input_finished()) return input_error();
    printf("Before: %d %d\n", a, b);
    swap_copies(a, b);
    printf("After value call: %d %d\n", a, b);
    swap_pointed_values(&a, &b);
    printf("After pointer call: %d %d\n", a, b);
    return EXIT_SUCCESS;
}
