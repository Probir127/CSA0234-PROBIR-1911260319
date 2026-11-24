/* Experiment 78: Date Validation and Comparison
 * Input: Two Gregorian dates as day month year; years 1..9999; invalid calendar dates are errors.
 */
#include "lab.h"

int main(void)
{
    LabDate a = lab_date(), b = lab_date();
    lab_require(lab_valid_date(a) && lab_valid_date(b), "invalid calendar date");
    long ka = lab_date_key(a), kb = lab_date_key(b);
    puts(ka < kb ? "First date is earlier" : (ka > kb ? "First date is later" : "Dates are equal"));
    lab_finish();
    return EXIT_SUCCESS;
}
