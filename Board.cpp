/*
This is a snake game built built by Rachel and Saad,
this file contains the implementations of the board class.
*/

#include "Board.hpp"

Board::Board(int m)  {
    direction = right;
    numRows = m;

    panel = new std::string*[numRows];
    for (int col = 0; col < numRows; col++)
        panel[col] = new std::string[numRows];
    clear(); // setting all the indices to " "
    snakeLength = 2;
    head = {numRows / 2, numRows / 2};
    panel[numRows/2][numRows/2] = " 🐸 ";
    tail = {numRows / 2, (numRows / 2) - 1};
    panel[numRows/2][(numRows/2)-1] = " 🟩 ";
}

void Board::setTarget(const int& goal) {
    target = goal;
}

void Board::clear() {
    for (int row = 0; row < numRows; row++)
        for (int col = 0; col < numRows; col++)
            panel[row][col] = " ";
}

void Board::print() {
    clear(); // setting all the indices to " "
    for (itr = snake.begin(); itr != snake.end(); itr++) {
        if (*itr == snake.front())
            panel[itr->row][itr->col] = " 🐸 ";
        else
            panel[itr->row][itr->col] = " 🟩 ";
    }
    for(int r = 0; r < numRows; r++) {
        std::cout << "+";
        for(int c = 0; c < numRows; c++) {
            std::cout << "----+";
        }
        std::cout << std::endl;
        std::cout << "|";
        for(int c = 0; c < numRows; c++) {
            if(panel[r][c] == " ") {
                std::cout << "    |";
            } else {
                std::cout << std::setw(4) << panel[r][c] << "|";
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

//Fix this function because what if it places the apple in an area completely
//surrounded by the snake, and had no choice but to die.
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
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numRows; j++) {
            if (panel[i][j] == " ") {
                Location empty;
                empty.row = i;
                empty.col = j;
                emptys.push_back(empty);
            }
        }
    }
    return emptys;
}

bool Board::isEmpty(const Location& square) const {
    return (panel[square.row][square.col] == " ");
}

void Board::pressUp() {
    if (direction != down)
        direction = up;
}

void Board::pressDown() {
    if (direction != up)
        direction = down;
}

void Board::pressLeft() {
    if (direction != right)
        direction = left;
}

void Board::pressRight() {
    if (direction != left)
        direction = right;
}

void Board::move() {
    if (direction == right) {
        if(head.col + 1 == numRows) {
            restart();
        } else {
            head.col += 1;
            snake.push_front(head);
            snake.pop_back();
        }
    } else if (direction == left) {
        if(head.col - 1 == -1) {
            restart();
        } else {
            head.col -= 1;
            snake.push_front(head);
            snake.pop_back();
        }
    } else if (direction == up) {
        if(head.row - 1 == -1) {
            restart();
        } else {
            head.row -= 1;
            snake.push_front(head);
            snake.pop_back();
        }
    } else if (direction == down) {
        if(head.row + 1 == numRows) {
            restart();
        } else {
            head.row += 1;
            snake.push_front(head);
            snake.pop_back();
        }
    }
}

void Board::restart() {
    setNonCanonicalMode(false);
    std::cout << "Game over, would you like to restart? (y)/(n): ";
    char response;
    std::cin >> response;
    if (response == 'y') {
        srand(time(NULL));
        int rows;
        do {
            std::cout << "Enter the size of the playable grid: ";
            std::cin >> rows;
            if (rows < 8)
                std::cerr << "Warning: Grid size must be greater than or equal to 8" << std::endl;
        } while (rows < 8);
        Board game(rows); //create a Board object with 8 rows and 8 columns.
        game.start();
    } else if (response == 'n') {
        std::cout << "Better luck next time!\n" << std::endl;
        exit(0);
    } else {
        std::cerr << "error in the restart" << std::endl;
        abort();
    }
}

void Board::start() {
    int round = 1;
    int row, col;
    selectRandomCell(row, col);
    int ch;
    // Set terminal to non-canonical mode aka not requiring the user the press enter for each keystroke
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
            //std::cout << "No input received within 1 second." << std::endl;
            //continue; // Continue the loop, wait for input again
            move();
            print();
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