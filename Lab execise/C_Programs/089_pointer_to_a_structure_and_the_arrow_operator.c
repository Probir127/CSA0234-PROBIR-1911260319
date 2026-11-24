/* Experiment 89: Pointer to a Structure and the Arrow Operator
 * Input: Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line.
 */
#include "lab.h"

int main(void)
{
    LabStudent student = lab_student();
    LabStudent *pointer = &student;
    printf("%d | %s | %.2f\n", pointer->roll, pointer->name, pointer->mark);
    lab_finish();
    return EXIT_SUCCESS;
}
