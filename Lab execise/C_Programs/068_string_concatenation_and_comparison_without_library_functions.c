/* Experiment 68: String Concatenation and Comparison Without Library Functions
 * Input: Two text lines, each up to 255 bytes; lexicographic byte comparison returns -1, 0 or 1.
 */
#include "lab.h"

int main(void)
{
    char a[LAB_TEXT], b[LAB_TEXT], joined[2 * LAB_TEXT];
    lab_line(a);
    lab_line(b);
    size_t i = 0, j = 0;
    while (a[i])
    {
        joined[i] = a[i];
        ++i;
    }
    while (b[j])
        joined[i++] = b[j++];
    joined[i] = '\0';
    i = 0;
    while (a[i] && a[i] == b[i])
        ++i;
    int comparison = (unsigned char)a[i] < (unsigned char)b[i]
                         ? -1
                         : ((unsigned char)a[i] > (unsigned char)b[i] ? 1 : 0);
    printf("Concatenated: %s\nComparison: %d\n", joined, comparison);
    lab_finish();
    return EXIT_SUCCESS;
}
