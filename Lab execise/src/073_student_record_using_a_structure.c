/* Experiment 73: Student Record Using a Structure
 * Input: Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line.
 */
#include "lab.h"

int main(void)
{
    LabStudent student = lab_student();
    lab_print_student(&student);
    lab_finish();
    return EXIT_SUCCESS;
}
