/* Experiment 115: Singly Linked List Insertion Deletion and Traversal
 * Input: Commands 1 integer (append), 2 integer (delete first match), 3 (display), 0 (exit).
 * Integers +/-1e6; capacity 100 nodes; at most 1000 commands.
 */
#include "lab.h"
typedef struct Node
{
    long long value;
    struct Node *next;
} Node;

int main(void)
{
    Node *head = NULL;
    int count = 0, commands = 0;
    while (1)
    {
        lab_require(++commands <= 1000, "too many commands");
        int choice = lab_int(0, 3);
        if (!choice)
            break;
        if (choice == 3)
        {
            int first = 1;
            for (Node *p = head; p; p = p->next)
            {
                printf("%s%lld", first ? "" : " ", p->value);
                first = 0;
            }
            putchar('\n');
            continue;
        }
        long long value = lab_integer(-1000000, 1000000);
        Node **link = &head;
        if (choice == 1)
        {
            lab_require(count < 100, "list full");
            while (*link)
                link = &(*link)->next;
            Node *node = malloc(sizeof *node);
            lab_require(node != NULL, "allocation failed");
            node->value = value;
            node->next = NULL;
            *link = node;
            ++count;
            puts("Inserted");
        }
        else
        {
            while (*link && (*link)->value != value)
                link = &(*link)->next;
            if (!*link)
                puts("Not found");
            else
            {
                Node *removed = *link;
                *link = removed->next;
                free(removed);
                --count;
                puts("Deleted");
            }
        }
    }
    while (head)
    {
        Node *next = head->next;
        free(head);
        head = next;
    }
    lab_finish();
    return EXIT_SUCCESS;
}
