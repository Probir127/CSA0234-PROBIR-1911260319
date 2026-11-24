/* Experiment 114: Menu Driven Calculator Using Function Pointers
 * Input: Commands 1=add, 2=subtract, 3=multiply, 4=divide, each followed by two reals +/-1e6; 0
 * exits. Divisor nonzero; at most 1000 commands.
 */
#include "lab.h"
static double add_values(double a, double b)
{
    return a + b;
}
static double subtract(double a, double b)
{
    return a - b;
}
static double multiply(double a, double b)
{
    return a * b;
}
static double divide(double a, double b)
{
    return a / b;
}

int main(void)
{
    double (*operations[])(double, double) = {add_values, subtract, multiply, divide};
    int commands = 0;
    while (1)
    {
        lab_require(++commands <= 1000, "too many commands");
        int choice = lab_int(0, 4);
        if (!choice)
            break;
        double a = lab_real(-1000000, 1000000), b = lab_real(-1000000, 1000000);
        lab_require(choice != 4 || b != 0, "division by zero");
        printf("Result: %.2f\n", operations[choice - 1](a, b));
    }
    lab_finish();
    return EXIT_SUCCESS;
}
