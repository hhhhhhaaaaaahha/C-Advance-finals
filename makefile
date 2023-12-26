.PHONY: clean

CC = gcc
CFLAGS = -Wfatal-errors -Wall -g

OBJ = ./src/*.c

all: clean fs
	
fs: main.c $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) main.c -o bin/main $(OBJ)

run: fs
	./bin/main

clean:
	rm -rf bin

test: test_clean $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) test/test.c -o bin/test
	./bin/test

test_clean:
	rm -rf bin/test
