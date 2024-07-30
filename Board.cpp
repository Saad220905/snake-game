// the autograder wants me to do this...
/*
Author: Saad Kashif
Course: CSCI-13500
Instructor: Tong Yi
Assignment: Game 1024 Task D, e.g., Task D

This code contains the constructors and
the methods of the Board class.
*/

#include "Board.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

Board::Board() : Board(8, 8) {
}

Board::Board(int m) : Board(m, m) {
}

Board::Board(int m, int n) {
    srand(1);
    if (m >= 1 && n >= 1) {
        numRows = m;
        numCols = n;
    } else {
        numRows = 8;
        numCols = 8;
    }

    panel = new int*[numRows];
    for (int row = 0; row < numRows; row++) {
        panel[row] = new int[numCols];
    }
    clear();
    max = 0;
    target = 32;
}

Board::~Board() {
    for (int row = 0; row < numRows; row++) {
        delete[] panel[row];
        panel[row] = nullptr;
    }
    delete[] panel;
    panel = nullptr;
}

int Board::getNumRows() const {
    return numRows;
}
int Board::getNumCols() const {
    return numCols;
}
int Board::getTarget() const {
    return target;
}
int Board::getMax() const {
    return max;
}

void Board::clear() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            panel[row][col] = 0;
        }
    }
}

void Board::print() const {
    for(int r = 0; r < numRows; r++) {
        cout << "+";
        for(int c = 0; c < numCols; c++) {
            cout << "----+";
        }
        cout << endl;
        cout << "|";
        for(int c = 0; c < numCols; c++) {
            if(panel[r][c] != 0) {
                cout << setw(4) << panel[r][c] << "|";
            } else {
                cout << "    |";
            }
        }
        cout << endl;
    }
    cout << "+";
    for(int c = 0; c < numCols; c++) {
        cout << "----+";
    }
    cout << endl;
}

class Location {
    public:
        int row;
        int col;
};

void Board::selectRandomCell(int& row, int& col) {
    vector<Location> zeros;
    Location cell;

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            if(panel[i][j] == 0) {
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

bool Board::noAdjacentSameValue() const {
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols - 1; j++)  {
            if(panel[i][j] == panel[i][j + 1]) {
                return false;
            }
        }
    }
    for(int i = 0; i < numRows - 1; i++) {
        for(int j = 0; j < numCols; j++)  {
            if(panel[i][j] == panel[i + 1][j]) {
                return false;
            }
        }
    }
    if(max < target) {
        return true;
    }
    return false;
}


void merge(vector<int>& nonZeros, int& max) {
    int i = 0;
    int size = nonZeros.size();
    while(i < size) {
        if(i + 1 < size && nonZeros[i + 1] == nonZeros[i]){
            nonZeros[i] *= 2;

            if (nonZeros[i] > max) {
                max = nonZeros[i];
            }
            nonZeros[i + 1] = 0;
            i += 2;
        } else {
            i++;
        }
    }
}

void Board::pressUp() {
    for(int col = 0; col < numCols; col++) {
        vector<int> nonZeros;
        for (int row = 0; row < numRows; row++) {
            if (panel[row][col] != 0){
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros, max);
        int row = 0;
        for(int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col] = nonZeros[i];
                row++;
            }
        }
        while (row < numRows) { 
            panel[row][col] = 0; 
            row++;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row,col);
}

void Board::pressDown() {
    for(int col = 0; col < numCols; col++) {
        vector<int> nonZeros;
        for (int row = numRows - 1; row >= 0; row--) {
            if (panel[row][col] != 0) {
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros, max);
        int row = numRows - 1;
        for(int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col] = nonZeros[i];
                row--;
            }
        }
        while (row >= 0) { 
            panel[row][col] = 0; 
            row--;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row,col);
}

void Board::pressLeft() {
    for(int row = 0; row < numRows; row++) {
        vector<int> nonZeros;
        for (int col = 0; col < numCols; col++) {
            if (panel[row][col] != 0) {
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros, max);
        int col = 0;
        for(int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col] = nonZeros[i];
                col++;
            }
        }
        while (col < numCols) { 
            panel[row][col] = 0; 
            col++;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row,col);
}

void Board::pressRight() {
    for(int row = 0; row < numRows; row++) {
        vector<int> nonZeros;
        for (int col = numCols-1; col >= 0; col--) {
            if (panel[row][col] != 0) {
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros, max);
        int col = numCols - 1;
        for(int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col] = nonZeros[i];
                col--;
            }
        }
        while (col >= 0) { 
            panel[row][col] = 0; 
            col--;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row, col);
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