/*
This is a snake game built built by Rachel and Saad,
this file contains the implementations of the board class.
*/

#include "Board.hpp"

//expected to never be used
Board::Board() : Board(8) {
}

Board::Board(int m) {
    directions direction = right;
    if (m >= 8)
        numRows = m;
    else
        numRows = 8;

    panel = new std::string*[numRows];
    for (int col = 0; col < numRows; col++) {
        panel[col] = new std::string[numRows];
    }
    clear();
    snakeLength = 2;
    head = {numRows/2,numRows/2};
    tail = {numRows/2,(numRows/2)-1};
    
    panel[numRows/2][numRows/2] = " 🐸 ";
    panel[numRows/2][(numRows/2)-1] = " 🟩 ";
    max = 0;
}

void Board::setTarget(const int& goal) {
    target = goal;
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
        panel[row][col] = " 🍎 ";
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
    return emptys;
}

void Board::pressUp() {
    direction = up;
}

void Board::pressDown() {
    direction = down;
}

void Board::pressLeft() {
    direction = left;
}

void Board::pressRight() {
    direction = right;
}

void Board::start() {
    int round = 1;
    int row, col;
    selectRandomCell(row, col);
    max = 1;
    int ch;
    // Set terminal to non-canonical mode
    setNonCanonicalMode(true);

    while (true) {
        if (getEmptys().size() <= 1) {
            std::cout << "Congratulation!" << std::endl;
            break;
        }

        // Set up the file descriptor set
        fd_set set;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);

        // Set up the timeout
        struct timeval timeout;
        timeout.tv_sec = 1;  // 1 second timeout
        timeout.tv_usec = 0;

        // Wait for input
        int result = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

        if (result == -1) {
            std::cerr << "Error using select()" << std::endl;
            break;
        } else if (result == 0) {
            std::cout << "No input received within 1 second." << std::endl;
            continue; // Continue the loop, wait for input again
        } else {
            ch = getchar();

            if (ch == 'S')
                break;

            if (ch == '\033') {
                getchar(); // Skip the '[' character
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
}

void Board::setNonCanonicalMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original settings
    }
}