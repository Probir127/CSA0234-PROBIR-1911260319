CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2
LDLIBS = -lm
BUILD_DIR ?= build
SOURCES := $(wildcard C_Programs/[0-9]*.c)
PROGRAMS := $(patsubst C_Programs/%.c,$(BUILD_DIR)/%,$(SOURCES))

.PHONY: all test sanitize clean
all: $(PROGRAMS)

$(BUILD_DIR)/%: C_Programs/%.c C_Programs/lab.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

test: all
	LAB_BUILD_DIR=$(BUILD_DIR) python3 tests/test_experiments.py

sanitize:
	$(MAKE) BUILD_DIR=build-sanitize CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Werror -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer' test

clean:
	rm -rf build build-sanitize
