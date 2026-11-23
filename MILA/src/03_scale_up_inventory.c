#include "input.h"

typedef struct {
    int quantity;
    int unit_price_cents;
} Item;

int main(void)
{
    int n;
    Item items[100];
    long long total_cents = 0;
    if (!read_int(&n, 1, 100)) return input_error();
    for (int i = 0; i < n; ++i) {
        if (!read_int(&items[i].quantity, 0, 10000) ||
            !read_int(&items[i].unit_price_cents, 0, 1000000)) return input_error();
        total_cents += (long long)items[i].quantity * items[i].unit_price_cents;
    }
    if (!input_finished()) return input_error();
    printf("Total cents: %lld\nTotal value: %lld.%02lld\n",
           total_cents, total_cents / 100, total_cents % 100);
    return EXIT_SUCCESS;
}
