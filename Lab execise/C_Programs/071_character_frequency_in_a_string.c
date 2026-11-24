/* Experiment 71: Character Frequency in a String
 * Input: One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated
 * otherwise. Output byte-code:count pairs in ascending byte order.
 */
#include "lab.h"

int main(void)
{
    char text[LAB_TEXT];
    int counts[UCHAR_MAX + 1] = {0};
    lab_line(text);
    for (size_t i = 0; text[i]; ++i)
        ++counts[(unsigned char)text[i]];
    for (unsigned i = 0; i <= UCHAR_MAX; ++i)
        if (counts[i])
            printf("%u:%d\n", i, counts[i]);
    lab_finish();
    return EXIT_SUCCESS;
}
