.PHONY: clean dir

CC = gcc
CPP = g++
CPP_FLAGS = -std=c++11 -Wfatal-errors -Wall
CFLAGS = -Wfatal-errors -Wall -g
TEST = test/*.h
OBJ = ./src/*.c

all: clean fs

test_all: clean test run_test
	
fs: main.c $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) main.c -o bin/main $(OBJ)

run: fs
	./bin/main

clean:
	rm -rf bin

test: clean dir $(OBJ) $(TEST)
	g++ $(CPP_FLAGS) $(OBJ) test/test.cpp -o bin/test -lgtest -lpthread

dir:
	mkdir -p bin

run_test: test
	./bin/test
