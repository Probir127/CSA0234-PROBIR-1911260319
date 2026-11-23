/* Experiment 79: Sort Students by Marks
 * Input: Count 1..100, then student records (roll line, name line, mark line); descending marks,
 * stable ties.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(1, 100);
    LabStudent students[100];
    lab_students(students, n);
    for (int i = 1; i < n; ++i)
    {
        LabStudent key = students[i];
        int j = i;
        while (j > 0 && students[j - 1].mark < key.mark)
        {
            students[j] = students[j - 1];
            --j;
        }
        students[j] = key;
    }
    for (int i = 0; i < n; ++i)
        lab_print_student(&students[i]);
    lab_finish();
    return EXIT_SUCCESS;
}
