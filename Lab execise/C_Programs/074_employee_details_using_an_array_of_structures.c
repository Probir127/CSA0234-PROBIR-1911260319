/* Experiment 74: Employee Details Using an Array of Structures
 * Input: Count 1..100; for each employee: unique positive ID line, name line, salary 0..1000000000
 * line.
 */
#include "lab.h"
typedef struct
{
    int id;
    char name[LAB_TEXT];
    double salary;
} Employee;

int main(void)
{
    int n = lab_int(1, 100);
    Employee staff[100];
    for (int i = 0; i < n; ++i)
    {
        staff[i].id = lab_int(1, 1000000);
        lab_line(staff[i].name);
        lab_require(staff[i].name[0], "empty name");
        staff[i].salary = lab_real(0, 1000000000);
        for (int j = 0; j < i; ++j)
            lab_require(staff[i].id != staff[j].id, "duplicate employee ID");
    }
    for (int i = 0; i < n; ++i)
        printf("%d | %s | %.2f\n", staff[i].id, staff[i].name, staff[i].salary);
    lab_finish();
    return EXIT_SUCCESS;
}
