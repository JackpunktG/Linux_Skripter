CC := gcc
CFLAGS := -O0 -g -Wall -Wextra -Wpedantic -std=c11 -Ilib

TARGET := out_test

SRC := src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean
