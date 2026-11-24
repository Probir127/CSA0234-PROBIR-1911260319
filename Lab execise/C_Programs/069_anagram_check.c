/* Experiment 69: Anagram Check
 * Input: Two lines containing ASCII letters and whitespace; ignore case and whitespace.
 */
#include "lab.h"

int main(void)
{
    char a[LAB_TEXT], b[LAB_TEXT];
    int frequencies[26] = {0};
    lab_line(a);
    lab_line(b);
    for (int which = 0; which < 2; ++which)
    {
        const char *s = which ? b : a;
        for (size_t i = 0; s[i]; ++i)
        {
            unsigned char ch = (unsigned char)s[i];
            if (isspace(ch))
                continue;
            ch = (unsigned char)tolower(ch);
            lab_require(ch >= 'a' && ch <= 'z', "letters and whitespace only");
            frequencies[ch - 'a'] += which ? -1 : 1;
        }
    }
    int same = 1;
    for (int i = 0; i < 26; ++i)
        if (frequencies[i])
            same = 0;
    puts(same ? "Anagrams" : "Not anagrams");
    lab_finish();
    return EXIT_SUCCESS;
}
