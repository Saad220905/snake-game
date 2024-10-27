# Snake Game

This is a classic Snake game implemented in C++ by Rachel and Saad. The game involves guiding a snake to eat food while avoiding collisions with walls or itself. The snake grows longer as it eats, making the game progressively more challenging.

## Features

- **Classic Snake Gameplay**: The game follows the traditional Snake game rules, where the snake grows as it consumes food, and the game ends if the snake runs into itself or the walls.
- **Dynamic Board Size**: The board size can be customized, with a minimum grid size of 8x8.
- **Arrow Key Controls**: Use the arrow keys to navigate the snake (Up, Down, Left, Right).
- **Random Food Placement**: The game randomly places food on the board for the snake to consume.
- **Restart Functionality**: Players can restart the game if they lose.
- **Terminal Non-Canonical Mode**: The game uses non-canonical mode for real-time controls.

## Getting Started

### Prerequisites

- C++ compiler (e.g., `g++`)
- Makefile support (optional)

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/snake-game.git
    cd snake-game
    ```

2. Compile the game:
    ```bash
    make
    ```

3. Run the game:
    ```bash
    ./snake_game
    ```

### Controls

- **Arrow Keys**: Move the snake in the corresponding direction.
- **`S` key**: Stop the game.
- **`y/n`**: Choose whether to restart the game after losing.

### Game Rules

1. **Objective**: Guide the snake to eat the food (🍎). Each time the snake eats, it grows longer.
2. **Avoid Collisions**: If the snake runs into the walls or itself, the game is over.
3. **Winning Condition**: Clear all available spaces on the board.

## Code Overview

### `Board` Class

The `Board` class manages the game's board, including the placement of the snake, food, and tracking game state.

- **Constructor**: Initializes the board size and sets up the initial snake position.
- **Movement Handling**: Moves the snake based on the current direction. Handles collisions with boundaries.
- **Food Placement**: Randomly places food on an empty cell in the grid.
- **Restart Functionality**: Restarts the game upon user input after losing.
- **Display**: Prints the board to the terminal, showing the snake (🟩) and food (🍎).

### Known Issues & Limitations

- The game implementation is incomplete, and some features may not work as expected.
- There may be edge cases not handled, such as extremely small or large board sizes.
- The game may not render well on some terminal environments.

## Future Enhancements

- **Add a scoring system** to track the player's score based on the number of foods consumed.
- **Implement levels or increasing difficulty** as the snake grows.
- **Add sound effects** for a more immersive experience.
- **Improve the graphical interface** using a library like SDL or ncurses.

## Contributing

Feel free to submit pull requests or report issues to improve the game.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

Enjoy the game and have fun guiding the snake to victory!