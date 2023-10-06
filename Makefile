CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -lmariadbcpp

all: todoc
todoc: main.o
	$(CC) -o todoc main.cpp $(CFLAGS)

clean:
	rm todoc

reload:
	rm todoc
	$(CC) -o todoc main.cpp $(CFLAGS)