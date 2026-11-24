/* Experiment 113: Array of Pointers to Strings
 * Input: Count 1..20 on its own line, then text lines; sort strings by exchanging their pointers.
 */
#include "lab.h"

int main(void)
{
    int n = lab_int(1, 20);
    char *strings[20] = {0};
    for (int i = 0; i < n; ++i)
    {
        char text[LAB_TEXT];
        lab_line(text);
        strings[i] = malloc(strlen(text) + 1);
        if (!strings[i])
        {
            for (int j = 0; j < i; ++j)
                free(strings[j]);
            lab_require(0, "allocation failed");
        }
        strcpy(strings[i], text);
    }
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (strcmp(strings[i], strings[j]) > 0)
            {
                char *temporary = strings[i];
                strings[i] = strings[j];
                strings[j] = temporary;
            }
    for (int i = 0; i < n; ++i)
    {
        puts(strings[i]);
        free(strings[i]);
    }
    lab_finish();
    return EXIT_SUCCESS;
}
