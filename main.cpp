#include <iostream>
#include "Board.hpp"
using namespace std;
/*
int main()
{
 Board game; //create a default Board object game
// game.print(); //test print method of game
 Board game2(4);
 //create a Board object with four rows
 //and four columns
// game2.print(); //test print methd of game2
 Board game3(3, 4);
 //create a Board object with three rows
 //and four columns
// game3.print(); //test print methd of game3
 return 0;
}
*/
int main() {
    srand(time(NULL));
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
    return 0;
}