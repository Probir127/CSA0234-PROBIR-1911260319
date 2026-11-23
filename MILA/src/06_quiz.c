#include "input.h"

int main(void)
{
    const char *questions[] = {
        "1. First index of a C array? 1) 0  2) 1  3) -1",
        "2. Address-of operator? 1) *  2) &  3) %",
        "3. Integer remainder operator? 1) /  2) +  3) %",
        "4. Stops a loop immediately? 1) break  2) continue  3) sizeof",
        "5. Binary search requires? 1) unique keys  2) sorted input  3) positive keys"
    };
    const int keys[] = {1, 2, 3, 1, 2};
    int answers[5], score = 0;
    for (int i = 0; i < 5; ++i)
        if (!read_int(&answers[i], 1, 3)) return input_error();
    if (!input_finished()) return input_error();
    for (int i = 0; i < 5; ++i) {
        puts(questions[i]);
        int correct = answers[i] == keys[i];
        score += correct;
        printf("%s; answer: %d\n", correct ? "Correct" : "Incorrect", keys[i]);
    }
    printf("Score: %d/5\n", score);
    return EXIT_SUCCESS;
}
