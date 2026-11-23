/* Experiment 120: Update a Record Using fseek and ftell Random Access
 * Input: Run experiment 119 first in the same directory. Input: target roll and replacement mark
 * 0..100. Updates students.dat in place; format is compiler/platform-specific.
 */
#include "lab.h"

int main(void)
{
    int target = lab_int(1, 1000000);
    double mark = lab_real(0, 100);
    FILE *file = fopen("students.dat", "r+b");
    lab_require(file != NULL, "run experiment 119 first");
    uint32_t count = 0;
    lab_require(fread(&count, sizeof count, 1, file) == 1 && count <= 100, "invalid binary header");
    lab_require(fseek(file, 0, SEEK_END) == 0, "seek failed");
    long size = ftell(file);
    lab_require(size >= 0 && (size_t)size == sizeof count + (size_t)count * sizeof(LabStudent),
                "invalid binary file length");
    lab_require(fseek(file, (long)sizeof count, SEEK_SET) == 0, "seek failed");
    int found = 0;
    for (uint32_t i = 0; i < count; ++i)
    {
        long position = ftell(file);
        lab_require(position >= 0, "ftell failed");
        LabStudent student;
        lab_require(fread(&student, sizeof student, 1, file) == 1, "record read failed");
        lab_require(memchr(student.name, '\0', sizeof student.name) != NULL && student.roll > 0 &&
                        isfinite(student.mark) && student.mark >= 0 && student.mark <= 100,
                    "invalid binary record");
        if (student.roll == target)
        {
            student.mark = mark;
            lab_require(fseek(file, position, SEEK_SET) == 0, "seek failed");
            lab_require(fwrite(&student, sizeof student, 1, file) == 1 && fflush(file) == 0,
                        "record update failed");
            lab_require(fseek(file, position, SEEK_SET) == 0 &&
                            fread(&student, sizeof student, 1, file) == 1,
                        "verification read failed");
            printf("Updated at byte: %ld\n", position);
            lab_print_student(&student);
            found = 1;
            break;
        }
    }
    lab_close(file);
    lab_require(found, "roll number not found");
    lab_finish();
    return EXIT_SUCCESS;
}
