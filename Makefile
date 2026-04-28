# This program uses Game and main modules with Raylib.
# Typing 'make' or 'make run' will create the executable file.

CC = g++ -std=c++23
CFLAGS = -g -Wall
RAYLIB_FLAGS = -lraylib -framework IOKit -framework Cocoa -framework OpenGL

# Homebrew paths for Raylib on macOS
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib

all: run

run: main.o Board.o 
	$(CC) -o run main.o Board.o $(LDFLAGS) $(RAYLIB_FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(INCLUDES)

Board.o: Board.cpp
	$(CC) -c Board.cpp $(INCLUDES)

clean: 
	$(RM) run *~ a.out *.o
