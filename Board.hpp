/*
This is a snake game built built by Rachel and Saad,
this file contains the declarations of the board class.
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>

struct Location {
    public:
        int row;
        int col;
};

class Board {
private:
    enum directions {up, down, left, right};
    directions direction;
    std::string** panel;
    std::vector<Location> snake;
       //two dimensional array with numRows rows and columns
    Location head;
    Location tail;
    int numRows;
    int max; //the current max in all cells of panel
        //apply dynamic memory for panel
        //so that panel has numRows rows and
        //numCols columns
    int target;
    int snakeLength;

public:
    Board(); //construct a 8 x 8 panel
    Board(int m); //construct a m x m panel
    void setTarget(const int& goal);
        //set target (goal) of the game
    void allocateMemory();
    int getNumRows() const;
    int getNumCols() const;
    int getTarget() const;
    int getMax() const;

    void clear();
        //set each cell of the panel to be zero
    void print() const;
        //print the panel
    std::vector<Location> getEmptys() const;
    void selectRandomCell(int& row, int& col);
        //select a random cell from empty cell
    void pressUp();
    void pressDown();
    void pressLeft();
    void pressRight(); //press right key
    void start(); //start the game
    void setNonCanonicalMode(bool enable);
};
#endif //BOARD_H