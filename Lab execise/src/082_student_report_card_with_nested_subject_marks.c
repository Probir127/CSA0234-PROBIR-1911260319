/* Experiment 82: Student Report Card with Nested Subject Marks
 * Input: Roll line, name line, then five marks 0..100; grade based on average (90/80/70/60
 * thresholds).
 */
#include "lab.h"
typedef struct
{
    double marks[5];
} Subjects;
typedef struct
{
    int roll;
    char name[LAB_TEXT];
    Subjects subjects;
} Report;

int main(void)
{
    Report report = {0};
    report.roll = lab_int(1, 1000000);
    lab_line(report.name);
    double total = 0;
    for (int i = 0; i < 5; ++i)
    {
        report.subjects.marks[i] = lab_real(0, 100);
        total += report.subjects.marks[i];
    }
    double average = total / 5;
    char grade = average >= 90   ? 'A'
                 : average >= 80 ? 'B'
                 : average >= 70 ? 'C'
                 : average >= 60 ? 'D'
                                 : 'F';
    printf("%d | %s\nTotal: %.2f\nAverage: %.2f\nGrade: %c\n", report.roll, report.name, total,
           average, grade);
    lab_finish();
    return EXIT_SUCCESS;
}
