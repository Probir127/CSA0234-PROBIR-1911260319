/* Experiment 70: Sort Strings in Alphabetical Order
 * Input: Count 0..20 on its own line, followed by one string per line; case-sensitive lexicographic
 * order.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(0, 20);
    char strings[20][LAB_TEXT];
    for (int i = 0; i < n; ++i)
        lab_line(strings[i]);
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (strcmp(strings[i], strings[j]) > 0)
            {
                char temporary[LAB_TEXT];
                strcpy(temporary, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temporary);
            }
    for (int i = 0; i < n; ++i)
        puts(strings[i]);
    lab_finish();
    return EXIT_SUCCESS;
}
