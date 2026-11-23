/* Experiment 117: Copy the Contents of One File to Another
 * Input: Source path line then destination path line; distinct files. Overwrites destination. POSIX
 * stat prevents copying onto the same inode.
 */
#include "lab.h"
#include <sys/stat.h>

int main(void)
{
    char source[LAB_TEXT], destination[LAB_TEXT];
    lab_line(source);
    lab_line(destination);
    lab_require(strcmp(source, destination) != 0, "source and destination are the same");
    struct stat a, b;
    lab_require(stat(source, &a) == 0, "source does not exist");
    if (stat(destination, &b) == 0)
        lab_require(a.st_dev != b.st_dev || a.st_ino != b.st_ino, "paths identify the same file");
    FILE *in = fopen(source, "rb");
    lab_require(in != NULL, "cannot open source");
    FILE *out = fopen(destination, "wb");
    if (!out)
    {
        lab_close(in);
        lab_require(0, "cannot open destination");
    }
    unsigned char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof buffer, in)) > 0)
        lab_require(fwrite(buffer, 1, n, out) == n, "copy write failed");
    lab_require(!ferror(in), "source read failed");
    lab_close(in);
    lab_close(out);
    puts("Copied");
    lab_finish();
    return EXIT_SUCCESS;
}
