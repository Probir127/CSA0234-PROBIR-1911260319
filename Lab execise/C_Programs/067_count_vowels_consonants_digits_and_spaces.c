/* Experiment 67: Count Vowels Consonants Digits and Spaces
 * Input: One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated
 * otherwise. Spaces means ASCII space, not every whitespace character.
 */
#include "lab.h"

int main(void)
{
    char text[LAB_TEXT];
    lab_line(text);
    int vowels = 0, consonants = 0, digits = 0, spaces = 0;
    for (size_t i = 0; text[i]; ++i)
    {
        unsigned char ch = (unsigned char)text[i];
        int lower = tolower(ch);
        if (strchr("aeiou", lower))
            ++vowels;
        else if (isalpha(ch))
            ++consonants;
        else if (isdigit(ch))
            ++digits;
        else if (ch == ' ')
            ++spaces;
    }
    printf("Vowels: %d\nConsonants: %d\nDigits: %d\nSpaces: %d\n", vowels, consonants, digits,
           spaces);
    lab_finish();
    return EXIT_SUCCESS;
}
