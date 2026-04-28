/*
This is a polished Snake game built using Raylib.
This file contains the declarations for the Game engine.
*/

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <deque>
#include <string>
#include "raylib.h"

// Location structure for coordinate management
struct Location {
    int x;
    int y;

    auto operator<=>(const Location&) const = default;
};

class Game {
public:
    Game(int gridSize, std::string snakeColorName);
    ~Game();

    void run(); // Main game loop

private:
    // Constants
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int padding = 60; // Padding for UI/Score
    
    // Game State
    enum class State { MENU, PLAYING, GAME_OVER };
    State currentState;

    int gridSize;
    int cellSize;
    int score;
    int highScore;
    float moveTimer;
    float moveSpeed; // Seconds per move

    std::deque<Location> snake;
    Location food;
    Location direction;
    Location nextDirection;
    Color snakeColor;
    bool directionChanged;

    // Initialization
    void initGame();
    void spawnFood();

    // Updates
    void update();
    void handleInput();
    void moveSnake();
    void checkCollision();

    // Drawing
    void draw();
    void drawMenu();
    void drawGame();
    void drawGameOver();
    void drawGrid();
    
    // Helpers
    Color getColorFromName(std::string name);
    Vector2 gridToScreen(int x, int y);
};

#endif // BOARD_HPP
