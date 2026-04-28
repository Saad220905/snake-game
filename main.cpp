#include <iostream>
#include <string>
#include <limits>
#include "Board.hpp"

using namespace std;

struct GameSettings {
    int rows;
    string snakeColor;
};

GameSettings getGameSettings() {
    int rows;
    string Answer, Color, snakeColor;
    
    cout << "--- Snake: Zen Edition ---\n" << endl;

    do {
        cout << "Enter the size of your space (12-25): ";
        if (!(cin >> rows)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            rows = 0;
        }
        if (rows < 12 || rows > 25)
            cerr << "Warning: A smaller space (12-25) is more tranquil." << endl;
    } while (rows < 12 || rows > 25);

    do {
        cout << "\nChoose a soft tone:\n"
             << "\tA: Sage\n\tB: Blush\n\tC: Lavender\n\tD: Sand\n\tE: Sky\n\n"
             << "Answer: ";
        cin >> Color;
        for (auto &c: Color) c = toupper(c);
    } while (Color.length() != 1 || Color[0] < 'A' || Color[0] > 'E');
    
    char colorChar = Color[0];
    if (colorChar == 'A') snakeColor = "🟩";
    else if (colorChar == 'B') snakeColor = "🟥";
    else if (colorChar == 'C') snakeColor = "🟪";
    else if (colorChar == 'D') snakeColor = "🟨";
    else if (colorChar == 'E') snakeColor = "🟦";
    
    return {rows, snakeColor};
}

int main() {
    GameSettings settings = getGameSettings();
    
    Game game(settings.rows, settings.snakeColor);
    game.run();

    return 0;
}
