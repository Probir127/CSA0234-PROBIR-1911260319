CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2
SOURCES := $(wildcard src/*.c)
PROGRAMS := $(patsubst src/%.c,build/%,$(SOURCES))

.PHONY: all test test-runner clean
all: $(PROGRAMS)

build/%: src/%.c src/input.h
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

test: all
	python3 tests/test_examples.py

test-runner: all
	python3 tests/test_runner.py

clean:
	rm -rf build
