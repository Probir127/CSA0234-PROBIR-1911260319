/* Experiment 105: Tower of Hanoi
 * Input: Disk count 1..10; move from A to C using B.
 */
#include "lab.h"
static void hanoi(int n, char from, char auxiliary, char to)
{
    if (n == 0)
        return;
    hanoi(n - 1, from, to, auxiliary);
    printf("%c -> %c\n", from, to);
    hanoi(n - 1, auxiliary, from, to);
}

int main(void)
{
    int n = lab_int(1, 10);
    hanoi(n, 'A', 'B', 'C');
    lab_finish();
    return EXIT_SUCCESS;
}
