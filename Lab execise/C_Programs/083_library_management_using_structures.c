/* Experiment 83: Library Management Using Structures
 * Input: Up to 1000 commands: 1 ID newline title newline author newline (add); 2 ID (borrow); 3 ID
 * (return); 4 (list); 0 (exit). Capacity 100 books.
 */
#include "lab.h"
typedef struct
{
    char name[LAB_TEXT];
} Author;
typedef struct
{
    int id;
    char title[LAB_TEXT];
    Author author;
    int borrowed;
} Book;

int main(void)
{
    Book books[100];
    int count = 0, commands = 0;
    while (1)
    {
        lab_require(++commands <= 1000, "too many commands");
        int command = lab_int(0, 4);
        if (command == 0)
            break;
        if (command == 4)
        {
            for (int i = 0; i < count; ++i)
                printf("%d | %s | %s | %s\n", books[i].id, books[i].title, books[i].author.name,
                       books[i].borrowed ? "Borrowed" : "Available");
            continue;
        }
        int id = lab_int(1, 1000000), index = -1;
        for (int i = 0; i < count; ++i)
            if (books[i].id == id)
                index = i;
        if (command == 1)
        {
            lab_require(index < 0 && count < 100, "duplicate ID or full library");
            Book book = {0};
            book.id = id;
            lab_line(book.title);
            lab_line(book.author.name);
            lab_require(book.title[0] && book.author.name[0], "empty book field");
            books[count++] = book;
            puts("Added");
        }
        else if (index < 0)
            puts("Not found");
        else if (command == 2)
        {
            if (books[index].borrowed)
                puts("Unavailable");
            else
            {
                books[index].borrowed = 1;
                puts("Borrowed");
            }
        }
        else
        {
            if (!books[index].borrowed)
                puts("Already available");
            else
            {
                books[index].borrowed = 0;
                puts("Returned");
            }
        }
    }
    lab_finish();
    return EXIT_SUCCESS;
}
