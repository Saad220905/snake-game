/*
This is a snake game built built by Rachel and Saad,
this file contains the declarations of the board class.
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
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

    bool operator==(const Location& otherL) const {
        return (row == otherL.row && col == otherL.col);
    }

    bool operator!=(const Location& otherL) const {
        return !(*this==otherL);
    }
};

class Board {
    std::deque<Location> snake;
    std::deque<Location>::iterator itr;
    enum directions {up, down, left, right};
    directions direction; //direction the snake is currently facing
    std::string** panel; //two dimensional array with numRows rows and columns
    Location head;
    Location tail;
    int numRows;
    int target;
    int snakeLength;
    void setTarget(const int& goal); //set target (goal) of the game
    void clear(); //set each cell of the panel to be zero
    void print(); //print the panel
    std::vector<Location> getEmptys() const;
    bool isEmpty(const Location& square) const;
    void selectRandomCell(int& row, int& col); //select a random cell from empty cell
    void pressUp();
    void pressDown();
    void pressLeft();
    void pressRight();
    void move();
    void restart();
    void setNonCanonicalMode(bool enable);

public:
    //Explicit cannot be used here
    Board(int m = 8); //construct a m x m panel
    void start(); //start the game
};
#endif //BOARD_H