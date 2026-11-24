/* Experiment 32: Grade Assignment Using else if Ladder
 * Input: Mark 0..100; A>=90, B>=80, C>=70, D>=60, otherwise F.
 */
#include "lab.h"

int main(void)
{
    double mark = lab_real(0, 100);
    char grade;
    if (mark >= 90)
        grade = 'A';
    else if (mark >= 80)
        grade = 'B';
    else if (mark >= 70)
        grade = 'C';
    else if (mark >= 60)
        grade = 'D';
    else
        grade = 'F';
    printf("Grade: %c\n", grade);
    lab_finish();
    return EXIT_SUCCESS;
}
