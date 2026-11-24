/* Experiment 31: Simple Calculator Using switch
 * Input: Number, operator (+ - * /), number; magnitudes <=1000000; divisor nonzero.
 */
#include "lab.h"

int main(void)
{
    double a = lab_real(-1000000, 1000000);
    char operation[LAB_TEXT];
    lab_token(operation);
    double b = lab_real(-1000000, 1000000), result = 0;
    lab_require(strlen(operation) == 1, "one operator required");
    switch (operation[0])
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        lab_require(b != 0, "division by zero");
        result = a / b;
        break;
    default:
        lab_require(0, "unknown operator");
    }
    printf("Result: %.2f\n", result);
    lab_finish();
    return EXIT_SUCCESS;
}
