/* Experiment 86: Inventory Management System
 * Input: Commands: 1 ID newline name newline quantity price-cents (add), 2 ID quantity (set), 3 ID
 * quantity (sell), 4 list, 0 exit. Capacity 100; qty 0..1e6, cents 0..1e9; at most 1000 commands.
 */
#include "lab.h"
typedef struct
{
    long long cents;
} Price;
typedef struct
{
    int id;
    char name[LAB_TEXT];
    int quantity;
    Price price;
} Product;

int main(void)
{
    Product products[100];
    int count = 0, commands = 0;
    while (1)
    {
        lab_require(++commands <= 1000, "too many commands");
        int command = lab_int(0, 4);
        if (!command)
            break;
        if (command == 4)
        {
            long long total = 0;
            for (int i = 0; i < count; ++i)
            {
                printf("%d | %s | %d | %lld cents\n", products[i].id, products[i].name,
                       products[i].quantity, products[i].price.cents);
                total += products[i].quantity * products[i].price.cents;
            }
            printf("Stock value cents: %lld\n", total);
            continue;
        }
        int id = lab_int(1, 1000000), index = -1;
        for (int i = 0; i < count; ++i)
            if (products[i].id == id)
                index = i;
        if (command == 1)
        {
            lab_require(index < 0 && count < 100, "duplicate ID or inventory full");
            Product product = {0};
            product.id = id;
            lab_line(product.name);
            lab_require(product.name[0], "empty product name");
            product.quantity = lab_int(0, 1000000);
            product.price.cents = lab_integer(0, 1000000000);
            products[count++] = product;
            puts("Added");
        }
        else
        {
            int quantity = lab_int(0, 1000000);
            if (index < 0)
                puts("Not found");
            else if (command == 2)
            {
                products[index].quantity = quantity;
                puts("Updated");
            }
            else if (quantity > products[index].quantity)
                puts("Insufficient stock");
            else
            {
                products[index].quantity -= quantity;
                puts("Sold");
            }
        }
    }
    lab_finish();
    return EXIT_SUCCESS;
}
