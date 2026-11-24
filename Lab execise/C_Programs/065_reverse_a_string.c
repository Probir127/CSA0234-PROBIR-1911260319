/* Experiment 65: Reverse a String
 * Input: One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated
 * otherwise.
 */
#include "lab.h"

int main(void)
{
    char text[LAB_TEXT];
    lab_line(text);
    size_t n = 0;
    while (text[n])
        ++n;
    for (size_t i = 0; i < n / 2; ++i)
    {
        char t = text[i];
        text[i] = text[n - 1 - i];
        text[n - 1 - i] = t;
    }
    puts(text);
    lab_finish();
    return EXIT_SUCCESS;
}
