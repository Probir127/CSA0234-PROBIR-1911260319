/* Experiment 34: Vowel or Consonant Using switch
 * Input: One ASCII alphabetic character; case-insensitive.
 */
#include "lab.h"

int main(void)
{
    char s[LAB_TEXT];
    lab_token(s);
    lab_require(strlen(s) == 1 && ((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z')),
                "ASCII letter required");
    switch (tolower((unsigned char)s[0]))
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        puts("Vowel");
        break;
    default:
        puts("Consonant");
    }
    lab_finish();
    return EXIT_SUCCESS;
}
