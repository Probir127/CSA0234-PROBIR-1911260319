/* Experiment 90: Union Demonstration
 * Input: Integer +/-1000000, real +/-1000000, then a text line. Assign and read one active member
 * at a time.
 */
#include "lab.h"
typedef union
{
    int integer;
    double real;
    char text[LAB_TEXT];
} Value;

int main(void)
{
    Value value;
    value.integer = lab_int(-1000000, 1000000);
    printf("Integer: %d\n", value.integer);
    value.real = lab_real(-1000000, 1000000);
    printf("Real: %.2f\n", value.real);
    lab_line(value.text);
    printf("Text: %s\n", value.text);
    lab_finish();
    return EXIT_SUCCESS;
}
