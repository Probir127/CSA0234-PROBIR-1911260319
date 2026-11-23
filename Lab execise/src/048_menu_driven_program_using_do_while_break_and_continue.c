/* Experiment 48: Menu Driven Program Using do while break and continue
 * Input: Commands: 1 a b (add), 2 n (square), 3 (skip), 0 (exit); numbers +/-1000000; at most 1000
 * commands.
 */
#include "lab.h"

int main(void)
{
    int commands = 0;
    do
    {
        lab_require(++commands <= 1000, "too many commands");
        int option = lab_int(0, 3);
        if (option == 0)
            break;
        if (option == 3)
        {
            puts("Skipped");
            continue;
        }
        long long a = lab_integer(-1000000, 1000000);
        if (option == 1)
        {
            long long b = lab_integer(-1000000, 1000000);
            printf("Sum: %lld\n", a + b);
        }
        else
            printf("Square: %lld\n", a * a);
    } while (1);
    lab_finish();
    return EXIT_SUCCESS;
}
