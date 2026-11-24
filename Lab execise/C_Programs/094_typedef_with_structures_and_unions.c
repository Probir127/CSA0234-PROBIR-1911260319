/* Experiment 94: typedef with Structures and Unions
 * Input: Item code, price 0..1e6, then quantity kind 1=count 0..1e6 or 2=weight 0..1e6, then
 * quantity.
 */
#include "lab.h"
typedef struct
{
    int code;
    double price;
} Item;
typedef union
{
    int count;
    double weight;
} Quantity;

int main(void)
{
    Item item = {lab_int(1, 1000000), lab_real(0, 1000000)};
    int kind = lab_int(1, 2);
    Quantity quantity;
    printf("Item: %d | %.2f\n", item.code, item.price);
    if (kind == 1)
    {
        quantity.count = lab_int(0, 1000000);
        printf("Count: %d\n", quantity.count);
    }
    else
    {
        quantity.weight = lab_real(0, 1000000);
        printf("Weight: %.2f\n", quantity.weight);
    }
    lab_finish();
    return EXIT_SUCCESS;
}
