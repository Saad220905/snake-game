# Snake: Polished Edition

A modern, visually appealing Snake game built with C++ and Raylib. This version moves away from the terminal and into a dedicated high-performance window with smooth animations, a scoring system, and refined aesthetics.

## New Features (GUI Version)

- **Proper Windowed Interface**: Runs in a dedicated 800x800 window using hardware-accelerated rendering.
- **Polished Visuals**:
    - **Rounded Snake Body**: Smooth segments with dynamic shading.
    - **Animated Snake Head**: Includes eyes that look in the direction of movement.
    - **Glow Effects**: Food and snake head have subtle visual enhancements.
- **Scoring System**: Real-time score tracking and persistent High Score.
- **Dynamic Difficulty**: The game speed increases as you eat more food, providing a greater challenge.
- **Interactive Menu**: Start screen and Game Over screen with smooth transitions.
- **Enhanced Grid Rendering**: subtle, modern grid background.

## Prerequisites

- C++20 or later
- [Raylib](https://www.raylib.com/) (`brew install raylib` on macOS)

## Getting Started

1. **Compile the game**:
    ```bash
    make
    ```

2. **Run the game**:
    ```bash
    ./run
    ```

## Controls

- **Arrow Keys**: Navigate the snake.
- **Enter**: Start game from menu or restart after Game Over.
- **M**: Return to main menu from Game Over screen.
- **ESC**: Close the window.

## Customization

Upon launching, the game allows you to customize your experience via the console:
1.  **Grid Size**: Choose a size between 10 and 40 for varying difficulty.
2.  **Snake Color**: Select from several vibrant colors (Green, Red, Purple, Yellow, Blue, Orange, Brown).

## Implementation Details

- **Engine**: Built using Raylib for high-performance 2D graphics.
- **State Machine**: Manages transitions between Menu, Playing, and Game Over states.
- **Modern C++**: Utilizes `std::deque` for snake body management and `operator<=>` for coordinate comparisons.

---

Enjoy the polished experience of a classic reimagined!
