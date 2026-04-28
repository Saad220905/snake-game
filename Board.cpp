#include "Board.hpp"
#include <algorithm>
#include <ctime>

// Zen / Soft Cafe Aesthetic Colors
const Color ZEN_BACKGROUND = { 235, 228, 215, 255 }; // Warm parchment
const Color ZEN_INK        = { 85, 75, 70, 255 };    // Soft charcoal/sepia
const Color ZEN_MATCHA     = { 158, 170, 140, 255 }; // Desaturated sage
const Color ZEN_BLUSH      = { 205, 170, 160, 255 }; // Muted rose
const Color ZEN_GRID       = { 220, 210, 195, 255 }; // Extremely faint grid
const Color ZEN_ACCENT     = { 180, 160, 140, 255 }; // Muted tan

Game::Game(int gridSize, std::string snakeColorName) 
    : currentState(State::MENU), 
      gridSize(gridSize), 
      score(0), 
      highScore(0),
      moveTimer(0),
      moveSpeed(0.4f) // Zen speed: very slow and deliberate
{
    cellSize = (screenWidth - 2 * padding) / gridSize;
    snakeColor = getColorFromName(snakeColorName);
    
    InitWindow(screenWidth, screenHeight, "Snake: Zen Edition");
    SetTargetFPS(60);
    
    initGame();
}

Game::~Game() {
    CloseWindow();
}

void Game::initGame() {
    snake.clear();
    int startX = gridSize / 2;
    int startY = gridSize / 2;
    
    snake.push_front({startX - 1, startY});
    snake.push_front({startX, startY});
    
    direction = {1, 0};
    nextDirection = direction;
    
    score = 0;
    moveSpeed = 0.4f; // Stay slow
    spawnFood();
}

void Game::spawnFood() {
    bool valid = false;
    while (!valid) {
        food = { GetRandomValue(0, gridSize - 1), GetRandomValue(0, gridSize - 1) };
        valid = true;
        for (const auto& segment : snake) {
            if (segment == food) {
                valid = false;
                break;
            }
        }
    }
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void Game::update() {
    if (currentState == State::MENU) {
        if (IsKeyPressed(KEY_ENTER)) currentState = State::PLAYING;
    } else if (currentState == State::PLAYING) {
        handleInput();
        
        moveTimer += GetFrameTime();
        if (moveTimer >= moveSpeed) {
            moveTimer = 0;
            moveSnake();
            checkCollision();
        }
    } else if (currentState == State::GAME_OVER) {
        if (IsKeyPressed(KEY_ENTER)) {
            initGame();
            currentState = State::PLAYING;
        }
        if (IsKeyPressed(KEY_M)) currentState = State::MENU;
    }
}

void Game::handleInput() {
    if (IsKeyPressed(KEY_UP) && direction.y == 0) nextDirection = {0, -1};
    if (IsKeyPressed(KEY_DOWN) && direction.y == 0) nextDirection = {0, 1};
    if (IsKeyPressed(KEY_LEFT) && direction.x == 0) nextDirection = {-1, 0};
    if (IsKeyPressed(KEY_RIGHT) && direction.x == 0) nextDirection = {1, 0};
}

void Game::moveSnake() {
    direction = nextDirection;
    Location newHead = { snake.front().x + direction.x, snake.front().y + direction.y };
    
    snake.push_front(newHead);
    
    if (newHead == food) {
        score += 1;
        if (score > highScore) highScore = score;
        // Hardly increase speed to keep it relaxing
        moveSpeed = std::max(0.3f, 0.4f - (score / 200.0f)); 
        spawnFood();
    } else {
        snake.pop_back();
    }
}

void Game::checkCollision() {
    Location head = snake.front();
    if (head.x < 0 || head.x >= gridSize || head.y < 0 || head.y >= gridSize) {
        currentState = State::GAME_OVER;
        return;
    }
    for (size_t i = 1; i < snake.size(); ++i) {
        if (head == snake[i]) {
            currentState = State::GAME_OVER;
            return;
        }
    }
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(ZEN_BACKGROUND);

    switch (currentState) {
        case State::MENU: drawMenu(); break;
        case State::PLAYING: drawGame(); break;
        case State::GAME_OVER: drawGameOver(); break;
    }

    EndDrawing();
}

void Game::drawMenu() {
    DrawText("Breathe", screenWidth/2 - MeasureText("Breathe", 30)/2, screenHeight/2 - 60, 30, ZEN_INK);
    DrawText("Zen Snake", screenWidth/2 - MeasureText("Zen Snake", 15)/2, screenHeight/2 - 10, 15, ZEN_ACCENT);
    DrawText("Press ENTER to begin", screenWidth/2 - MeasureText("Press ENTER to begin", 18)/2, screenHeight/2 + 60, 18, ZEN_ACCENT);
}

void Game::drawGame() {
    drawGrid();
    
    // Draw Food (Soft Circle)
    Vector2 foodPos = gridToScreen(food.x, food.y);
    DrawCircleV({foodPos.x + cellSize/2, foodPos.y + cellSize/2}, cellSize/3, ZEN_BLUSH);
    DrawCircleLinesV({foodPos.x + cellSize/2, foodPos.y + cellSize/2}, cellSize/3 + 1, ColorAlpha(ZEN_INK, 0.2f));

    // Draw Snake
    for (size_t i = 0; i < snake.size(); ++i) {
        Vector2 pos = gridToScreen(snake[i].x, snake[i].y);
        Color color = (i == 0) ? snakeColor : ColorAlpha(snakeColor, 0.6f);
        
        // Softer segments
        float shrink = (i == 0) ? 4.0f : 6.0f;
        DrawRectangleRounded({pos.x + shrink, pos.y + shrink, (float)cellSize - shrink*2, (float)cellSize - shrink*2}, 0.8f, 16, color);
        
        if (i == 0) {
            // Subtle eyes
            DrawCircle(pos.x + cellSize/3, pos.y + cellSize/2, 1.5f, ZEN_INK);
            DrawCircle(pos.x + 2*cellSize/3, pos.y + cellSize/2, 1.5f, ZEN_INK);
        }
    }

    // UI - Minimal and Softer
    DrawText(TextFormat("collected: %i", score), padding, 30, 18, ZEN_ACCENT);
    DrawText(TextFormat("record: %i", highScore), screenWidth - padding - MeasureText(TextFormat("record: %i", highScore), 18), 30, 18, ZEN_ACCENT);
}

void Game::drawGameOver() {
    DrawRectangle(0, 0, screenWidth, screenHeight, ColorAlpha(ZEN_BACKGROUND, 0.9f));
    DrawText("A moment's rest.", screenWidth/2 - MeasureText("A moment's rest.", 25)/2, screenHeight/2 - 30, 25, ZEN_INK);
    DrawText("Press ENTER to continue", screenWidth/2 - MeasureText("Press ENTER to continue", 15)/2, screenHeight/2 + 40, 15, ZEN_ACCENT);
}

void Game::drawGrid() {
    // Fainter grid
    for (int i = 0; i <= gridSize; i++) {
        DrawLine(padding + i * cellSize, padding, padding + i * cellSize, padding + gridSize * cellSize, ZEN_GRID);
        DrawLine(padding, padding + i * cellSize, padding + gridSize * cellSize, padding + i * cellSize, ZEN_GRID);
    }
}

Vector2 Game::gridToScreen(int x, int y) {
    return { (float)(padding + x * cellSize), (float)(padding + y * cellSize) };
}

Color Game::getColorFromName(std::string name) {
    if (name == "🟩") return ZEN_MATCHA;
    if (name == "🟥") return { 210, 180, 170, 255 }; // Muted Blush
    if (name == "🟪") return { 180, 175, 190, 255 }; // Muted Lavender
    if (name == "🟨") return { 220, 205, 180, 255 }; // Sand
    if (name == "🟦") return { 170, 185, 195, 255 }; // Muted Sky
    if (name == "🟧") return { 210, 190, 160, 255 }; // Soft Terracotta
    if (name == "🟫") return ZEN_ACCENT;
    return ZEN_MATCHA;
}
