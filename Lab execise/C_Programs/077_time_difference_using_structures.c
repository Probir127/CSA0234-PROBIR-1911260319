/* Experiment 77: Time Difference Using Structures
 * Input: Two same-day times as hour minute second; 0..23,0..59,0..59. Output the absolute
 * difference.
 */
#include "lab.h"

int main(void)
{
    LabTime first = lab_time(), second = lab_time();
    int difference = abs(lab_seconds(second) - lab_seconds(first));
    printf("%02d:%02d:%02d\n", difference / 3600, difference % 3600 / 60, difference % 60);
    lab_finish();
    return EXIT_SUCCESS;
}
