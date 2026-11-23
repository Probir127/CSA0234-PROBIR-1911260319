/* Experiment 75: Complex Number Addition and Multiplication
 * Input: Real and imaginary parts of two complex numbers, each +/-1000000.
 */
#include "lab.h"
typedef struct
{
    double real, imaginary;
} Complex;

int main(void)
{
    Complex a = {lab_real(-1000000, 1000000), lab_real(-1000000, 1000000)},
            b = {lab_real(-1000000, 1000000), lab_real(-1000000, 1000000)};
    Complex sum = {a.real + b.real, a.imaginary + b.imaginary},
            product = {a.real * b.real - a.imaginary * b.imaginary,
                       a.real * b.imaginary + a.imaginary * b.real};
    printf("Sum: %.2f %.2fi\nProduct: %.2f %.2fi\n", sum.real, sum.imaginary, product.real,
           product.imaginary);
    lab_finish();
    return EXIT_SUCCESS;
}
