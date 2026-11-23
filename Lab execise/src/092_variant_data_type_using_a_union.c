/* Experiment 92: Variant Data Type Using a Union
 * Input: Tag 1=int, 2=real, 3=text, followed by that value; text starts on next line. Magnitudes
 * <=1000000.
 */
#include "lab.h"
enum Kind
{
    INTEGER = 1,
    REAL,
    TEXT
};
typedef struct
{
    enum Kind tag;
    union
    {
        int integer;
        double real;
        char text[LAB_TEXT];
    } data;
} Variant;

int main(void)
{
    Variant value;
    value.tag = (enum Kind)lab_int(1, 3);
    switch (value.tag)
    {
    case INTEGER:
        value.data.integer = lab_int(-1000000, 1000000);
        printf("Integer: %d\n", value.data.integer);
        break;
    case REAL:
        value.data.real = lab_real(-1000000, 1000000);
        printf("Real: %.2f\n", value.data.real);
        break;
    case TEXT:
        lab_line(value.data.text);
        printf("Text: %s\n", value.data.text);
        break;
    }
    lab_finish();
    return EXIT_SUCCESS;
}
