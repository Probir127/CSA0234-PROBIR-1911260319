CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

all: server client

server: server.c http.c http.h protocol.h
	$(CC) $(CFLAGS) -pthread server.c http.c -o server

client: client.c protocol.h
	$(CC) $(CFLAGS) client.c -o client

check: all
	python3 test_system.py

.PHONY: all check
