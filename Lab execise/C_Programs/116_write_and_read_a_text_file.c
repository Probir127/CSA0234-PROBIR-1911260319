/* Experiment 116: Write and Read a Text File
 * Input: One text line (up to 255 bytes); overwrites notes.txt in the current directory and reads
 * it back.
 */
#include "lab.h"

int main(void)
{
    char text[LAB_TEXT];
    lab_line(text);
    FILE *file = fopen("notes.txt", "w");
    lab_require(file != NULL, "cannot create notes.txt");
    lab_require(fprintf(file, "%s\n", text) >= 0, "write failed");
    lab_close(file);
    file = fopen("notes.txt", "r");
    lab_require(file != NULL, "cannot reopen notes.txt");
    printf("Read: ");
    int ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
    lab_require(!ferror(file), "read failed");
    lab_close(file);
    lab_finish();
    return EXIT_SUCCESS;
}
