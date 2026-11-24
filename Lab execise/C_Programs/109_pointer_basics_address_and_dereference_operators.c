/* Experiment 109: Pointer Basics Address and Dereference Operators
 * Input: Integer +/-1000000; the printed address varies between executions.
 */
#include "lab.h"

int main(void)
{
    int value = lab_int(-1000000, 1000000);
    int *pointer = &value;
    printf("Value: %d\nAddress: %p\nDereferenced: %d\n", value, (void *)pointer, *pointer);
    *pointer += 1;
    printf("Updated: %d\n", value);
    lab_finish();
    return EXIT_SUCCESS;
}
