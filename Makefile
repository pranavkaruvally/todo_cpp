CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wshadow

all: todoc
todoc: main.o
	$(CC) $(CFLAGS) -o todoc main.o

todoc.o: main.cpp todo.h
	$(CC) $(CFLAGS) -c main.cpp