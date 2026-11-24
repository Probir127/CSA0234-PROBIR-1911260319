/* Experiment 9: Temperature Conversion Celsius to Fahrenheit and Back
 * Input: Direction C or F, then temperature -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    char direction[LAB_TEXT];
    lab_token(direction);
    double t = lab_real(-1000000, 1000000);
    lab_require(strlen(direction) == 1 && (direction[0] == 'C' || direction[0] == 'F'),
                "direction must be C or F");
    if (direction[0] == 'C')
        printf("Fahrenheit: %.2f\n", t * 9 / 5 + 32);
    else
        printf("Celsius: %.2f\n", (t - 32) * 5 / 9);
    lab_finish();
    return EXIT_SUCCESS;
}
