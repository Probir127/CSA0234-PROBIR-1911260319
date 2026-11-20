#define _POSIX_C_SOURCE 200809L
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protocol.h"
static int prompt(const char *label, char *out, size_t cap) {
    printf("%s", label); fflush(stdout);
    if (!fgets(out, (int)cap, stdin)) return -1;
    char *nl = strchr(out, '\n');
    if (!nl) { int c; while ((c = getchar()) != '\n' && c != EOF) {} puts("Input too long."); return 1; }
    *nl = 0;
    if (!*out || strpbrk(out, "\t\r")) { puts("Enter a nonempty value without tabs."); return 1; }
    return 0;
}
int main(int argc, char **argv) {
    const char *host = argc > 1 ? argv[1] : "127.0.0.1";
    char *end; long port = argc > 2 ? strtol(argv[2], &end, 10) : 5050;
    if (argc > 3 || port < 1 || port > 65535 || (argc > 2 && (!*argv[2] || *end))) { fprintf(stderr, "Usage: %s [server_ipv4] [port]\n", argv[0]); return 1; }
    signal(SIGPIPE, SIG_IGN);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0}; addr.sin_family = AF_INET; addr.sin_port = htons((unsigned short)port);
    if (fd < 0 || inet_pton(AF_INET, host, &addr.sin_addr) != 1) { fprintf(stderr, "Invalid socket or IPv4 address\n"); return 1; }
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr))) { perror("connect (start the server first)"); close(fd); return 1; }
    puts("Connected to the library server.");
    for (;;) {
        char choice[16], a[160], b[160], request[LINE_SIZE], response[LINE_SIZE];
        puts("\n1. List books\n2. Search books\n3. Add book\n4. Borrow book\n5. Return book\n0. Exit");
        int rc = prompt("Choice: ", choice, sizeof(choice));
        if (rc < 0) break;
        if (rc) continue;
        if (!strcmp(choice, "0")) break;
        if (!strcmp(choice, "1")) strcpy(request, "LIST\n");
        else if (!strcmp(choice, "2")) {
            if (prompt("Title or author (case-sensitive): ", a, sizeof(a))) continue;
            snprintf(request, sizeof(request), "SEARCH\t%s\n", a);
        } else if (!strcmp(choice, "3")) {
            if (prompt("Title: ", a, sizeof(a)) || prompt("Author: ", b, sizeof(b))) continue;
            snprintf(request, sizeof(request), "ADD\t%s\t%s\n", a, b);
        } else if (!strcmp(choice, "4") || !strcmp(choice, "5")) {
            if (prompt("Book ID: ", a, sizeof(a)) || prompt("Borrower name: ", b, sizeof(b))) continue;
            snprintf(request, sizeof(request), "%s\t%s\t%s\n", !strcmp(choice, "4") ? "BORROW" : "RETURN", a, b);
        } else { puts("Choose 0 to 5."); continue; }
        if (send_text(fd, request)) { puts("Connection lost."); close(fd); return 1; }
        for (;;) {
            if (read_line(fd, response, sizeof(response))) { puts("Server disconnected (idle timeout is 60 seconds)."); close(fd); return 1; }
            if (!strcmp(response, "END")) break;
            puts(response);
        }
    }
    send_text(fd, "QUIT\n"); close(fd); return 0;
}
