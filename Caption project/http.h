#ifndef LIBRARY_HTTP_H
#define LIBRARY_HTTP_H
/* Serve one request; dispatch decoded commands to the library service. */
void http_serve(int fd, char *request, void (*handle)(int, char *));
#endif
