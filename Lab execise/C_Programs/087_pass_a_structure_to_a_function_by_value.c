/* Experiment 87: Pass a Structure to a Function by Value
 * Input: Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line. The copied
 * mark is raised by five, capped at 100.
 */
#include "lab.h"
static void raise_copy(LabStudent student)
{
    student.mark = fmin(100, student.mark + 5);
    printf("Inside copy: %.2f\n", student.mark);
}

int main(void)
{
    LabStudent student = lab_student();
    raise_copy(student);
    printf("Caller: %.2f\n", student.mark);
    lab_finish();
    return EXIT_SUCCESS;
}
