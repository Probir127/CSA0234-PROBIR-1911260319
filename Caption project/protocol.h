#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>
#define LINE_SIZE 8192
/* TCP is a byte stream: send completely and receive one newline-delimited frame. */
static int send_text(int fd, const char *s) {
    size_t n = 0;
    while (s[n]) n++;
    while (n) {
        ssize_t k = send(fd, s, n, 0);
        if (k < 0 && errno == EINTR) continue;
        if (k <= 0) return -1;
        s += k; n -= (size_t)k;
    }
    return 0;
}
static int read_line(int fd, char *out, size_t cap) {
    size_t n = 0;
    for (;;) {
        char c;
        ssize_t k = recv(fd, &c, 1, 0);
        if (k < 0 && errno == EINTR) continue;
        if (k <= 0) return -1;
        if (c == '\n') { out[n] = 0; return 0; }
        if (n + 1 >= cap || c == '\0') return -1;
        out[n++] = c;
    }
}
#endif
