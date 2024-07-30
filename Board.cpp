/*
This is a snake game built built by Rachel and Saad,
this file contains the implementations of the board class.
*/

#include "Board.hpp"

Board::Board() : Board(8) {
}

Board::Board(int m) {
    srand(1);
    if (m >= 8)
        numRows = m;
    else
        numRows = 8;

    panel = new std::string*[numRows];
    for (int col = 0; col < numRows; col++) {
        panel[col] = new std::string[numRows];
    }
    clear();
    max = 0;
}

int Board::getNumRows() const {
    return numRows;
}

int Board::getMax() const {
    return max;
}

void Board::clear() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numRows; col++) {
            panel[row][col] = " ";
        }
    }
}

void Board::print() const {
    for(int r = 0; r < numRows; r++) {
        std::cout << "+";
        for(int c = 0; c < numRows; c++) {
            std::cout << "----+";
        }
        std::cout << std::endl;
        std::cout << "|";
        for(int c = 0; c < numRows; c++) {
            if(panel[r][c] != " ") {
                std::cout << std::setw(4) << panel[r][c] << "|";
            } else {
                std::cout << "    |";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "+";
    for(int c = 0; c < numRows; c++) {
        std::cout << "----+";
    }
    std::cout << std::endl;
}

void Board::selectRandomCell(int& row, int& col) {
    std::vector<Location> emptys = getEmptys();
    if(emptys.size() > 0) {
        int index = rand() % emptys.size();
        row = emptys[index].row;
        col = emptys[index].col;
        panel[row][col] = "🍎";
        print();
    }
    if(emptys.size() == 0 || emptys.size() == 1) {
        std::cout << "Congratulations!" << std::endl;
        exit(0);
    }
}

std::vector<Location> Board::getEmptys() const {
    std::vector<Location> emptys;
    Location cell;

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numRows; j++) {
            if(panel[i][j] == " ") {
                cell.row = i;
                cell.col = j;
                emptys.push_back(cell);
            }
        }
    }
}

void Board::pressUp() {
    
}

void Board::pressDown() {

}

void Board::pressLeft() {

}

void Board::pressRight() {

}

void Board::start() {
    int round = 1;
    int row, col;
    selectRandomCell(row, col);
    selectRandomCell(row, col);
    max = 1;

    char ch;
    while (true) {
        if (getEmptys().size() <= 1) {
            std::cout << "Congratulation!" << std::endl;
            break;
        }

        ch = getchar();
        if (ch == 'S')
            break;

    if (ch == '\033') {
        getchar();
        switch(getchar()) {
            case 'A':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press UP. " << std::endl;
                pressUp();
                round++;
                break;
            case 'B':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press DOWN. " << std::endl;
                pressDown();
                round++;
                break;
            case 'C':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press RIGHT. " << std::endl;
                pressRight();
                round++;
                break;
            case 'D':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press LEFT. " << std::endl;
                pressLeft();
                round++;
                break;
            
            }
        }
    }
}