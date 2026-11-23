/* Experiment 84: Bank Account Management Using Structures
 * Input: Account ID line, owner line, starting balance cents 0..1000000000000; commands 1
 * positive-cents deposit, 2 positive-cents withdraw, 3 show, 0 exit. At most 1000 commands.
 */
#include "lab.h"
typedef struct
{
    char name[LAB_TEXT];
} Owner;
typedef struct
{
    int id;
    Owner owner;
    long long cents;
} Account;

int main(void)
{
    Account account = {0};
    account.id = lab_int(1, 1000000);
    lab_line(account.owner.name);
    account.cents = lab_integer(0, 1000000000000LL);
    int commands = 0;
    while (1)
    {
        lab_require(++commands <= 1000, "too many commands");
        int command = lab_int(0, 3);
        if (!command)
            break;
        if (command == 3)
        {
            printf("%d | %s | %lld cents\n", account.id, account.owner.name, account.cents);
            continue;
        }
        long long amount = lab_integer(1, 1000000000);
        if (command == 1)
            account.cents += amount;
        else if (amount > account.cents)
        {
            puts("Insufficient funds");
            continue;
        }
        else
            account.cents -= amount;
        printf("Balance cents: %lld\n", account.cents);
    }
    lab_finish();
    return EXIT_SUCCESS;
}
