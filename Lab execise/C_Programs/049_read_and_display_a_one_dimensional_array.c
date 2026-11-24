/* Experiment 49: Read and Display a One Dimensional Array
 * Input: Count 0..100, then that many integers -1000000..1000000.
 */
#include "lab.h"

int main(void)
{
    long long a[LAB_CAP];
    int n = lab_array(a, 0);
    lab_print_array(a, n);
    lab_finish();
    return EXIT_SUCCESS;
}
