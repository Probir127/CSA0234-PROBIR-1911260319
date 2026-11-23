/* Experiment 81: Employee with Address and Date of Birth
 * Input: ID line, name line, street line, city line, then DOB day month year.
 */
#include "lab.h"
typedef struct
{
    char street[LAB_TEXT], city[LAB_TEXT];
} Address;
typedef struct
{
    int id;
    char name[LAB_TEXT];
    Address address;
    LabDate birth;
} Employee;

int main(void)
{
    Employee employee = {0};
    employee.id = lab_int(1, 1000000);
    lab_line(employee.name);
    lab_line(employee.address.street);
    lab_line(employee.address.city);
    employee.birth = lab_date();
    lab_require(lab_valid_date(employee.birth), "invalid birth date");
    printf("%d | %s\n%s, %s\nDOB: %04d-%02d-%02d\n", employee.id, employee.name,
           employee.address.street, employee.address.city, employee.birth.year,
           employee.birth.month, employee.birth.day);
    lab_finish();
    return EXIT_SUCCESS;
}
