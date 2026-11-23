/* Experiment 23: Days of the Week Using enum
 * Input: Day 1..7, Monday=1.
 */
#include "lab.h"

int main(void)
{
    enum Day
    {
        MONDAY = 1,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };
    enum Day day = (enum Day)lab_int(MONDAY, SUNDAY);
    const char *names[] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                           "Friday", "Saturday", "Sunday"};
    puts(names[day - 1]);
    lab_finish();
    return EXIT_SUCCESS;
}
