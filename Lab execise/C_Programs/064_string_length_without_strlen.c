/* Experiment 64: String Length Without strlen
 * Input: One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated
 * otherwise.
 */
#include "lab.h"

int main(void)
{
    char text[LAB_TEXT];
    lab_line(text);
    size_t length = 0;
    while (text[length] != '\0')
        ++length;
    printf("Length: %zu\n", length);
    lab_finish();
    return EXIT_SUCCESS;
}
