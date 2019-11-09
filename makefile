CC=gcc
CFLAGS+= -I./include -Wall -Wextra -lstdc++ #-Werror 
BIN_DIR=bin
SRC_DIR=src
BIN_NAME=huffman

SRC_FILES=$(SRC_DIR)/main.c

all:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC_FILES) -o bin/$(BIN_NAME)

project:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC_FILES) -o bin/$(BIN_NAME)

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

run:
	./$(BIN_DIR)/$(BIN_NAME)