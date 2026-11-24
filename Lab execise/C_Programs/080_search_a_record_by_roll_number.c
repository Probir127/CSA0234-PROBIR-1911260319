/* Experiment 80: Search a Record by Roll Number
 * Input: Count 1..100, student records (roll/name/mark lines), then target roll.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(1, 100);
    LabStudent students[100];
    lab_students(students, n);
    int target = lab_int(1, 1000000), found = 0;
    for (int i = 0; i < n; ++i)
        if (students[i].roll == target)
        {
            lab_print_student(&students[i]);
            found = 1;
            break;
        }
    if (!found)
        puts("Not found");
    lab_finish();
    return EXIT_SUCCESS;
}
