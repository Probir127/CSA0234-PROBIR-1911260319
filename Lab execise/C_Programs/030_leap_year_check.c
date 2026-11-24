/* Experiment 30: Leap Year Check
 * Input: Gregorian year 1..9999.
 */
#include "lab.h"

int main(void)
{
    int year = lab_int(1, 9999);
    puts(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0) ? "Leap year" : "Not a leap year");
    lab_finish();
    return EXIT_SUCCESS;
}
