/*
This is a snake game built built by Rachel and Saad,
this file contains the implementations of the board class.
*/
#include "Board.hpp"

Board::Board(int m, std::string snakeBody) : numRows(m), direction(right), directionChanged(false), snakeLength(2), snakeBody(snakeBody) {
    if (m < 8)
        throw std::invalid_argument("Board size must be at least 8x8");
    panel = new std::string*[numRows];
    for (int i = 0; i < numRows; i++) 
        panel[i] = new std::string[numRows];
    clear();
    head = {numRows / 2, numRows / 2};
    tail = {numRows / 2, (numRows / 2) - 1};
    snake.push_back(tail);
    snake.push_back(head);
    panel[head.row][head.col] = " 🐸 ";
    panel[tail.row][tail.col] = " 🟩 ";
}

Board::~Board() {
    for (int i = 0; i < numRows; i++)
        delete[] panel[i];
    delete[] panel;
}

void Board::clear() {
    for (int row = 0; row < numRows; row++)
        for (int col = 0; col < numRows; col++)
            panel[row][col] = " ";
}

void Board::print() {
    // Temporary board to preserve apples
    std::string** tempPanel = new std::string*[numRows];
    for (int i = 0; i < numRows; i++) {
        tempPanel[i] = new std::string[numRows];
        for (int j = 0; j < numRows; j++) {
            if (panel[i][j] == " 🍎 ") {
                tempPanel[i][j] = " 🍎 ";
            } else {
                tempPanel[i][j] = " ";
            }
        }
    }
    // Draw snake on temporary board
    for (auto itr = snake.begin(); itr != snake.end(); itr++) {
        if (*itr == snake.front()) {
            tempPanel[itr->row][itr->col] = " 🐸 ";
        } else {
            tempPanel[itr->row][itr->col] = " " + snakeBody + " ";
        }
    }
    // Update main panel and print
    for(int r = 0; r < numRows; r++) {
        std::cout << "+";
        for(int c = 0; c < numRows; c++) {
            std::cout << "----+";
        }
        std::cout << std::endl;
        std::cout << "|";
        for(int c = 0; c < numRows; c++) {
            panel[r][c] = tempPanel[r][c];
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
    // Cleanup temporary panel memory
    for (int i = 0; i < numRows; i++)
        delete[] tempPanel[i];
    delete[] tempPanel;
}

void Board::selectRandomCell(int& row, int& col) {
    std::vector<Location> validCells = getEmptys();
    if (!validCells.empty()) {
        int index = rand() % validCells.size();
        row = validCells[index].row;
        col = validCells[index].col;
        panel[row][col] = " 🍎 ";
        print();
    } else {
        std::cout << "Congratulations! You filled the grid!" << std::endl;
        exit(0);
    }
}

std::vector<Location> Board::getEmptys() const {
    std::vector<Location> validEmptys;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numRows; j++) {
            if (panel[i][j] == " ") {
                bool hasNeighbor = false;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < numRows && nj >= 0 && nj < numRows && panel[ni][nj] == " ") {
                            hasNeighbor = true;
                            break;
                        }
                    }
                    if (hasNeighbor) break;
                }
                if (hasNeighbor) {
                    validEmptys.push_back({i, j});
                }
            }
        }
    }
    return validEmptys;
}

void Board::pressUp() {
    if (direction != down && !directionChanged) {
        direction = up;
        directionChanged = true;
    }
}

void Board::pressDown() {
    if (direction != up && !directionChanged) {
        direction = down;
        directionChanged = true;
    }
}

void Board::pressLeft() {
    if (direction != right && !directionChanged) {
        direction = left;
        directionChanged = true;
    }
}

void Board::pressRight() {
    if (direction != left && !directionChanged) {
        direction = right;
        directionChanged = true;
    }
}

void Board::move() {
    Location nextHead = head;
    directionChanged = false;
    switch (direction) {
        case right: nextHead.col += 1; break;
        case left:  nextHead.col -= 1; break;
        case up:    nextHead.row -= 1; break;
        case down:  nextHead.row += 1; break;
    }
    if (nextHead.row < 0 || nextHead.row >= numRows || 
        nextHead.col < 0 || nextHead.col >= numRows || 
        panel[nextHead.row][nextHead.col] == " 🟩 ") {
        std::cout << "\nGame Over! Snake hit a wall or itself!\n";
        restart();
        return;
    }
    snake.push_front(nextHead);
    head = nextHead;
    if (panel[nextHead.row][nextHead.col] == " 🍎 ") {
        snakeLength++;
        int row, col;
        selectRandomCell(row, col);
    } else {
        snake.pop_back();
    }
    print();
}

void Board::setNonCanonicalMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

void Board::start() {
    srand(static_cast<unsigned>(time(nullptr)));
    int round = 1;
    int row, col;
    selectRandomCell(row, col);
    setNonCanonicalMode(true);
    while (true) {
        if (getEmptys().empty()) {
            std::cout << "Congratulations! You've won!" << std::endl;
            break;
        }
        fd_set set;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 300000;  // 300ms
        int result = select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout);
        if (result == -1) {
            std::cerr << "Error in select()" << std::endl;
            break;
        } else if (result == 0) {
            move();
        } else {
            int ch = getchar();
            if (ch == 'S' || ch == 's') {
                break;
            }
            if (ch == '\033') {  // Arrow key was pressed
                getchar();  // Skip the '[' character
                switch(getchar()) {  // The actual arrow key
                    case 'A': 
                        pressUp();
                        std::cout << "Round " << std::setw(4) << round++ << ": UP" << std::endl;
                        break;
                    case 'B': 
                        pressDown();
                        std::cout << "Round " << std::setw(4) << round++ << ": DOWN" << std::endl;
                        break;
                    case 'C': 
                        pressRight();
                        std::cout << "Round " << std::setw(4) << round++ << ": RIGHT" << std::endl;
                        break;
                    case 'D': 
                        pressLeft();
                        std::cout << "Round " << std::setw(4) << round++ << ": LEFT" << std::endl;
                        break;
                }
                move();
            }
        }
    }
    setNonCanonicalMode(false);
}

void Board::restart() {
    setNonCanonicalMode(false);
    std::cout << "Would you like to restart? (y/n): ";
    char response;
    std::cin >> response;
    if (response == 'y' || response == 'Y') {
        int rows;
        std::string Answer, Color, snakeBody;
        do {
            std::cout << "Enter the size of the playable grid: ";
            std::cin >> rows;
            if (rows < 8)
                std::cerr << "Warning: Grid size must be greater than or equal to 8" << std::endl;
        } while (rows < 8);
        std::cout << std::endl;
        do {
        std::cout << "What do you want the snake's body to be made out of:\n\tA: A color\n\tB: A Custom Emoji (or character)\n\nAnswer: ";
        std::cin >> Answer;
        } while (!(Answer == "A" || Answer == "B" || Answer == "a" || Answer == "b"));
        std::cout << std::endl;
        if(Answer == "A" || Answer == "a") {
            do {
                std::cout << "Pick a color:\n\tA: 🟩\n\tB: 🟥\n\tC: 🟪\n\tD: 🟨\n\tE: 🟦\n\tF: 🟧\n\tG: 🟫\n\nAnswer: ";
                std::cin >> Color;
            } while (!(Answer == "A" || Answer == "B"|| Answer == "C"|| Answer == "D"|| Answer == "E"|| Answer == "F"|| Answer == "G" ||
                    Answer == "a" || Answer == "b"|| Answer == "c"|| Answer == "d"|| Answer == "e"|| Answer == "f"|| Answer == "f"));
            if (Color == "A" || Color == "a") snakeBody = "🟩";
            else if (Color == "B" || Color == "b") snakeBody = "🟥";
            else if (Color == "C" || Color == "c") snakeBody = "🟪";
            else if (Color == "D" || Color == "d") snakeBody = "🟨";
            else if (Color == "E" || Color == "e") snakeBody = "🟦";
            else if (Color == "F" || Color == "f") snakeBody = "🟧";
            else if (Color == "G" || Color == "g") snakeBody = "🟫";
            std::cout << std::endl;
        } else {
            do {
                std::cout << "Pick any emoji (or character)\n\nAnswer: ";
                std::cin >> snakeBody;
            } while (snakeBody.length() != 1 || snakeBody == " ");
            std::cout << std::endl;
        }
        Board game(rows, snakeBody); //create a Board object with 8 rows and 8 columns.
        game.start();
    } else if (response == 'n' || response == 'N') {
        std::cout << "Thanks for playing!\n";
        exit(0);
    } else {
        std::cerr << "Invalid input. Exiting game.\n";
        exit(1);
    }
}