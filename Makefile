CC=gcc
CFLAGS=-std=c99

LIB=lib
BIN=bin
LIB_TESTS=$(LIB)/test
BIN_TESTS=$(BIN)/test

all: tests

tests:
	$(CC) $(CFLAGS) $(LIB_TESTS)/bitboard.c -o $(BIN_TESTS)/bitboard
	$(CC) $(CFLAGS) $(LIB_TESTS)/bitboard-mask.c -o $(BIN_TESTS)/bitboard-mask
	$(CC) $(CFLAGS) $(LIB_TESTS)/squares.c -o $(BIN_TESTS)/squares
	$(CC) $(CFLAGS) $(LIB_TESTS)/position-initial.c -o $(BIN_TESTS)/position-initial
	$(CC) $(CFLAGS) $(LIB_TESTS)/FEN-recognize.c -o $(BIN_TESTS)/FEN-recognize
	$(CC) $(CFLAGS) $(LIB_TESTS)/move-parse.c -o $(BIN_TESTS)/move-parse

clean:
	rm -f bin/*.o
	rm -f bin/test/*.o
