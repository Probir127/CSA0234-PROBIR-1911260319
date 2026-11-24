/* Experiment 88: Pass a Structure to a Function by Reference
 * Input: Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line. A pointer
 * is passed by value to modify the original mark, capped at 100.
 */
#include "lab.h"
static void raise_mark(LabStudent *student)
{
    student->mark = fmin(100, student->mark + 5);
}

int main(void)
{
    LabStudent student = lab_student();
    raise_mark(&student);
    printf("Caller: %.2f\n", student.mark);
    lab_finish();
    return EXIT_SUCCESS;
}
