/*
This is a snake game built built by Rachel and Saad,
this file contains the declarations of the board class.
*/

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>

// Location structure for coordinate management
struct Location {
    int row;
    int col;

    // Assignment operator
    Location& operator=(const Location& other) {
        if (this != &other) {
            row = other.row;
            col = other.col;
        }
        return *this;
    }

    // Comparison operators
    bool operator==(const Location& otherL) const {
        return row == otherL.row && col == otherL.col;
    }

    bool operator!=(const Location& otherL) const {
        return !(*this == otherL);
    }
};

class Board {
public:
    // Constructor
    explicit Board(int m, std::string snakeBody); // Construct a m x m panel
    
    // Destructor (moved to public)
    ~Board();
    
    // Game control
    void start(); // Start the game

private:
    // Enums
    enum directions {up, down, left, right};

    // Member variables
    std::deque<Location> snake;
    std::deque<Location>::iterator itr;
    directions direction;        // Direction the snake is currently facing
    std::string** panel;        // Two dimensional array with numRows rows and columns
    Location head;
    Location tail;
    std::string snakeBody;
    int numRows;
    int snakeLength;
    bool directionChanged;

    // Board operations
    void clear();               // Set each cell of the panel to be empty
    void print();               // Print the panel
    std::vector<Location> getEmptys() const;
    void selectRandomCell(int& row, int& col); // Select a random empty cell

    // Movement controls
    void pressUp();
    void pressDown();
    void pressLeft();
    void pressRight();
    void move();

    // Game state management
    void restart();
    void setNonCanonicalMode(bool enable);
};

#endif // BOARD_HPP