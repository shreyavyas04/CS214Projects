CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
BUILD_DIR = build

all: memgrind

$(BUILD_DIR)/mymalloc.o: $(SRC_DIR)/mymalloc.c $(SRC_DIR)/mymalloc.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/memgrind: $(SRC_DIR)/memgrind.c $(BUILD_DIR)/mymalloc.o $(SRC_DIR)/mymalloc.h
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/mymalloc.o -o $@

memgrind: $(BUILD_DIR)/memgrind

clean:
	rm -f $(BUILD_DIR)/memgrind $(BUILD_DIR)/mymalloc.o

.PHONY: all clean
