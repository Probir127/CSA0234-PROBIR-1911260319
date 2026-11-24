/* Experiment 85: Employee Payroll Processing
 * Input: Employee count 1..100; each: ID line, name line, basic pay 0..1e9, HRA percent 0..100, DA
 * percent 0..100, deductions 0..1e9. Deductions cannot exceed gross pay.
 */
#include "lab.h"
typedef struct
{
    double basic, hra, da, deductions;
} Pay;
typedef struct
{
    int id;
    char name[LAB_TEXT];
    Pay pay;
} Payroll;

int main(void)
{
    int n = lab_int(1, 100);
    Payroll employees[100];
    for (int i = 0; i < n; ++i)
    {
        Payroll *p = &employees[i];
        p->id = lab_int(1, 1000000);
        lab_line(p->name);
        p->pay.basic = lab_real(0, 1000000000);
        p->pay.hra = lab_real(0, 100);
        p->pay.da = lab_real(0, 100);
        p->pay.deductions = lab_real(0, 1000000000);
    }
    for (int i = 0; i < n; ++i)
    {
        Payroll *p = &employees[i];
        double gross = p->pay.basic * (1 + (p->pay.hra + p->pay.da) / 100);
        lab_require(p->pay.deductions <= gross, "deductions exceed gross pay");
        printf("%d | %s | Gross: %.2f | Net: %.2f\n", p->id, p->name, gross,
               gross - p->pay.deductions);
    }
    lab_finish();
    return EXIT_SUCCESS;
}
