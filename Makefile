# This program uses Board and main modules.
# Typing 'make' or 'make run' will create the executable file.

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++ -std=c++23
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
all: run

# To create the executable file run we need the object files
run:  main.o Board.o 
	$(CC) -o run main.o Board.o
	$(RM) *.o

# To create the object file, we need the source
main.o:  main.cpp
	$(CC) -c main.cpp

# To create the object file, we need the source
Board.o:  Board.cpp
	$(CC) -c Board.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
clean: 
	$(RM) run *~ a.out
