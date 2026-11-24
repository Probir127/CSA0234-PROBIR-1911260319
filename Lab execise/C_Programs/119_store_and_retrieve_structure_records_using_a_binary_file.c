/* Experiment 119: Store and Retrieve Structure Records Using a Binary File
 * Input: Count 0..100, then unique student records (roll/name/mark lines). Overwrites students.dat;
 * raw struct format is for the same compiler/platform only.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(0, 100);
    LabStudent students[100];
    lab_students(students, n);
    uint32_t count = (uint32_t)n;
    FILE *file = fopen("students.dat", "wb");
    lab_require(file != NULL, "cannot create students.dat");
    lab_require(fwrite(&count, sizeof count, 1, file) == 1 &&
                    fwrite(students, sizeof *students, (size_t)n, file) == (size_t)n,
                "binary write failed");
    lab_close(file);
    file = fopen("students.dat", "rb");
    lab_require(file != NULL, "cannot reopen students.dat");
    uint32_t restored = 0;
    lab_require(fread(&restored, sizeof restored, 1, file) == 1 && restored <= 100,
                "invalid binary header");
    for (uint32_t i = 0; i < restored; ++i)
    {
        LabStudent student;
        lab_require(fread(&student, sizeof student, 1, file) == 1, "truncated binary record");
        lab_print_student(&student);
    }
    lab_close(file);
    lab_finish();
    return EXIT_SUCCESS;
}
