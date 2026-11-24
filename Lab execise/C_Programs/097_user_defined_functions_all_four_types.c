/* Experiment 97: User Defined Functions All Four Types
 * Input: Two integers +/-1000000. Demonstrates argument/return combinations.
 */
#include "lab.h"
static void greet(void)
{
    puts("No args/no return");
}
static void show(long long n)
{
    printf("Args/no return: %lld\n", n);
}
static int fixed_value(void)
{
    return 5;
}
static long long add_values(long long a, long long b)
{
    return a + b;
}

int main(void)
{
    long long a = lab_integer(-1000000, 1000000), b = lab_integer(-1000000, 1000000);
    greet();
    show(a);
    printf("No args/return: %d\nArgs/return: %lld\n", fixed_value(), add_values(a, b));
    lab_finish();
    return EXIT_SUCCESS;
}
