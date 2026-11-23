/* Experiment 95: Railway Ticket Reservation System
 * Input: Capacity 1..20; commands 1 seat newline passenger-name newline (book), 2 seat (cancel), 3
 * list, 0 exit. At most 1000 commands.
 */
#include "lab.h"
typedef struct
{
    char name[LAB_TEXT];
} Passenger;
typedef struct
{
    int reserved;
    Passenger passenger;
} Seat;
typedef struct
{
    int capacity;
    Seat seats[20];
} Train;

int main(void)
{
    int capacity = lab_int(1, 20), commands = 0;
    Train train = {0};
    train.capacity = capacity;
    while (1)
    {
        lab_require(++commands <= 1000, "too many commands");
        int command = lab_int(0, 3);
        if (!command)
            break;
        if (command == 3)
        {
            for (int i = 0; i < train.capacity; ++i)
                printf("%d | %s\n", i + 1,
                       train.seats[i].reserved ? train.seats[i].passenger.name : "Available");
            continue;
        }
        int seat = lab_int(1, capacity) - 1;
        if (command == 1)
        {
            char name[LAB_TEXT];
            lab_line(name);
            lab_require(name[0], "empty passenger name");
            if (train.seats[seat].reserved)
                puts("Seat already reserved");
            else
            {
                train.seats[seat].reserved = 1;
                strcpy(train.seats[seat].passenger.name, name);
                printf("Booked: %d\n", seat + 1);
            }
        }
        else if (!train.seats[seat].reserved)
            puts("Seat already empty");
        else
        {
            train.seats[seat].reserved = 0;
            printf("Cancelled: %d\n", seat + 1);
        }
    }
    lab_finish();
    return EXIT_SUCCESS;
}
