/*
This is a snake game built built by Rachel and Saad,
this file contains the implementations of the board class.
*/

#include "Board.hpp"
using namespace std;

Board::Board() : Board(8) {
}

Board::Board(int m) {
    srand(1);
    if (m >= 8)
        numRows = m;
    else
        numRows = 8;

    panel = new string*[numRows];
    for (int col = 0; col < numRows; col++) {
        panel[col] = new string[numRows];
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
        cout << "+";
        for(int c = 0; c < numRows; c++) {
            cout << "----+";
        }
        cout << endl;
        cout << "|";
        for(int c = 0; c < numRows; c++) {
            if(panel[r][c] != " ") {
                cout << setw(4) << panel[r][c] << "|";
            } else {
                cout << "    |";
            }
        }
        cout << endl;
    }
    cout << "+";
    for(int c = 0; c < numRows; c++) {
        cout << "----+";
    }
    cout << endl;
}

void Board::selectRandomCell(int& row, int& col) {
    vector<Location> zeros;
    Location cell;

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numRows; j++) {
            if(panel[i][j] == " ") {
                cell.row = i;
                cell.col = j;
                zeros.push_back(cell);
            }
        }
    }
    if(zeros.size() > 0) {
        int index = rand() % zeros.size();
        row = zeros[index].row;
        col = zeros[index].col;
        panel[row][col] = 1;
        print();
    }
    if(zeros.size() == 0 || zeros.size() == 1) {
        if(noAdjacentSameValue()) {
            if(max < target) {
                cout << "Game over. Try again." << endl;
            } else {
                cout << "Congratulations!" << endl;
            }
            exit(0);
        } else {
            return;
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
        if (max >= target) {
            cout << "Congratulation!" << endl;
            break;
        }

        ch = getchar();
        if (ch == 'S')
            break;

    if (ch == '\033') {
        getchar();
        switch(getchar()) {
            case 'A':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press UP. " << "Goal: " << target << endl;
                pressUp();
                round++;
                break;
            case 'B':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press DOWN. " << "Goal: " << target << endl;
                pressDown();
                round++;
                break;
            case 'C':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press RIGHT. " << "Goal: " << target << endl;
                pressRight();
                round++;
                break;
            case 'D':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press LEFT. " << "Goal: " << target << endl;
                pressLeft();
                round++;
                break;
            
            }
        }
    }
}