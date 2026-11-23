/* Experiment 96: Polynomial Addition Using Structures
 * Input: First term count 0..20 and coefficient/exponent pairs, then second polynomial; coefficient
 * +/-1e6, exponent 0..100. Output nonzero coefficient/exponent pairs descending.
 */
#include "lab.h"
typedef struct
{
    long long coefficient;
    int exponent;
} Term;

int main(void)
{
    Term polynomials[2][20];
    int counts[2];
    long long combined[101] = {0};
    for (int p = 0; p < 2; ++p)
    {
        counts[p] = lab_int(0, 20);
        for (int i = 0; i < counts[p]; ++i)
        {
            polynomials[p][i].coefficient = lab_integer(-1000000, 1000000);
            polynomials[p][i].exponent = lab_int(0, 100);
            combined[polynomials[p][i].exponent] += polynomials[p][i].coefficient;
        }
    }
    Term result[101];
    int n = 0;
    for (int exponent = 100; exponent >= 0; --exponent)
        if (combined[exponent])
        {
            result[n].coefficient = combined[exponent];
            result[n++].exponent = exponent;
        }
    if (!n)
        puts("0 0");
    else
        for (int i = 0; i < n; ++i)
            printf("%lld %d\n", result[i].coefficient, result[i].exponent);
    lab_finish();
    return EXIT_SUCCESS;
}
