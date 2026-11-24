/* Experiment 91: Memory Size Comparison of Structure and Union
 * Input: No input; sizes depend on platform alignment and padding.
 */
#include "lab.h"
struct StructData
{
    int integer;
    double real;
    char text[16];
};
union UnionData
{
    int integer;
    double real;
    char text[16];
};

int main(void)
{
    printf("Structure size: %zu\nUnion size: %zu\n", sizeof(struct StructData),
           sizeof(union UnionData));
    printf("Union covers every member: %s\n",
           sizeof(union UnionData) >= sizeof(double) && sizeof(union UnionData) >= 16 ? "yes"
                                                                                      : "no");
    lab_finish();
    return EXIT_SUCCESS;
}
