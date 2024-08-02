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
int main()
{
//     string s = "😊";
//     cout << s;
    Board game(8); //create a Board object with 8 rows and 8 columns.
    game.start();
    return 0;
}