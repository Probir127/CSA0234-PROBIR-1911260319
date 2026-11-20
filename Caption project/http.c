#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "protocol.h"
#include "http.h"
void http_serve(int fd, char *request, void (*handle)(int, char *)) {
    char method[16], path[LINE_SIZE];
    if (sscanf(request, "%15s %8191s", method, path) != 2) return;
    char header[LINE_SIZE];
    while (!read_line(fd, header, sizeof(header)) && strcmp(header, "\r") && *header) {}
    if (!strcmp(method, "GET")) {
        char *query = strchr(path, '?');
        if (query) *query = 0;
        const char *file = NULL, *type = "text/html; charset=utf-8";
        if (!strcmp(path, "/")) file = "interface.html";
        else if (!strcmp(path, "/books")) file = "books.html";
        else if (!strcmp(path, "/stock")) file = "stock.html";
        else if (!strcmp(path, "/holds")) file = "holds.html";
        else if (!strcmp(path, "/members")) file = "members.html";
        else if (!strcmp(path, "/add")) file = "add.html";
        else if (!strncmp(path, "/loans?", 7) || !strcmp(path, "/loans")) file = "loans.html";
        else if (!strcmp(path, "/style.css")) { file = "style.css"; type = "text/css"; }
        else if (!strcmp(path, "/app.js")) { file = "app.js"; type = "application/javascript"; }
        FILE *f = file ? fopen(file, "r") : NULL;
        if (!f) { send_text(fd, "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\ninterface.html missing"); return; }
        char response[256];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nCache-Control: no-store\r\nX-Content-Type-Options: nosniff\r\nConnection: close\r\n\r\n", type);
        send_text(fd, response);
        char chunk[4096];
        while (fgets(chunk, sizeof(chunk), f)) if (send_text(fd, chunk)) break;
        fclose(f);
    } else if (!strcmp(method, "POST") && !strncmp(path, "/api?", 5)) {
        char decoded[LINE_SIZE]; size_t n = 0;
        for (size_t i = 5; path[i] && n + 1 < sizeof(decoded); i++) {
            unsigned int c;
            if (path[i] == '%' && path[i+1] && path[i+2] && isxdigit((unsigned char)path[i+1]) && isxdigit((unsigned char)path[i+2]) && sscanf(path+i+1, "%2x", &c) == 1) {
                if (!c || c == 10 || c == 13) return;
                decoded[n++] = (char)c; i += 2;
            } else decoded[n++] = path[i];
        }
        decoded[n] = 0;
        send_text(fd, "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\nCache-Control: no-store\r\nConnection: close\r\n\r\n");
        handle(fd, decoded);
    } else send_text(fd, "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\nNot found");
}
