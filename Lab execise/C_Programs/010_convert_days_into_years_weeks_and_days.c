/* Experiment 10: Convert Days into Years Weeks and Days
 * Input: Days 0..1000000000; use fixed 365-day years and 7-day weeks.
 */
#include "lab.h"

int main(void)
{
    long long days = lab_integer(0, 1000000000);
    printf("Years: %lld\nWeeks: %lld\nDays: %lld\n", days / 365, days % 365 / 7, days % 365 % 7);
    lab_finish();
    return EXIT_SUCCESS;
}
