/* Experiment 72: Substring Pattern Search in a String
 * Input: Text line then pattern line; return first zero-based index or -1; empty pattern matches at
 * 0.
 */
#include "lab.h"

int main(void)
{
    char text[LAB_TEXT], pattern[LAB_TEXT];
    lab_line(text);
    lab_line(pattern);
    size_t n = strlen(text), m = strlen(pattern);
    int index = -1;
    if (m <= n)
        for (size_t i = 0; i <= n - m; ++i)
        {
            size_t j = 0;
            while (j < m && text[i + j] == pattern[j])
                ++j;
            if (j == m)
            {
                index = (int)i;
                break;
            }
        }
    printf("Index: %d\n", index);
    lab_finish();
    return EXIT_SUCCESS;
}
