/* Experiment 66: Palindrome String Check
 * Input: One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated
 * otherwise.
 */
#include "lab.h"

int main(void)
{
    char text[LAB_TEXT];
    lab_line(text);
    size_t n = strlen(text);
    int palindrome = 1;
    for (size_t i = 0; i < n / 2; ++i)
        if (text[i] != text[n - 1 - i])
            palindrome = 0;
    puts(palindrome ? "Palindrome" : "Not palindrome");
    lab_finish();
    return EXIT_SUCCESS;
}
