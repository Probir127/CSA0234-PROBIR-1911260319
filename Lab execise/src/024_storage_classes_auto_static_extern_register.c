/* Experiment 24: Storage Classes auto static extern register
 * Input: No input.
 */
#include "lab.h"
int lab_shared = 10;
static int next_call(void)
{
    static int calls = 0;
    return ++calls;
}

int main(void)
{
    auto int local = 3;
    register int fast = 5;
    extern int lab_shared;
    printf("auto=%d register=%d extern=%d\n", local, fast, lab_shared);
    int first = next_call();
    int second = next_call();
    printf("static calls: %d %d\n", first, second);
    lab_finish();
    return EXIT_SUCCESS;
}
