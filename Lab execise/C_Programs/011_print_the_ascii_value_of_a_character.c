/* Experiment 11: Print the ASCII Value of a Character
 * Input: One non-whitespace ASCII character.
 */
#include "lab.h"

int main(void)
{
    char s[LAB_TEXT];
    lab_token(s);
    lab_require(strlen(s) == 1 && (unsigned char)s[0] <= 127, "one ASCII character required");
    printf("ASCII: %u\n", (unsigned)(unsigned char)s[0]);
    lab_finish();
    return EXIT_SUCCESS;
}
