/* Experiment 118: Count Characters Words and Lines in a File
 * Input: File path line. Characters are bytes; words are whitespace-delimited; a nonempty
 * unterminated final line counts as a line.
 */
#include "lab.h"

int main(void)
{
    char path[LAB_TEXT];
    lab_line(path);
    FILE *file = fopen(path, "rb");
    lab_require(file != NULL, "cannot open file");
    unsigned long long characters = 0, words = 0, lines = 0;
    int in_word = 0, ch, last = '\n';
    while ((ch = fgetc(file)) != EOF)
    {
        ++characters;
        if (ch == '\n')
            ++lines;
        if (isspace((unsigned char)ch))
            in_word = 0;
        else if (!in_word)
        {
            ++words;
            in_word = 1;
        }
        last = ch;
    }
    lab_require(!ferror(file), "file read failed");
    lab_close(file);
    if (characters && last != '\n')
        ++lines;
    printf("Characters: %llu\nWords: %llu\nLines: %llu\n", characters, words, lines);
    lab_finish();
    return EXIT_SUCCESS;
}
