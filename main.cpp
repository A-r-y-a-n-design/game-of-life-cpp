// Conway's Game of Life - a beginner-friendly C++ project
//
// The rules (applied to every cell, every generation):
//   1. A live cell with 2 or 3 live neighbors stays alive.
//   2. A live cell with any other number of neighbors dies.
//   3. A dead cell with exactly 3 live neighbors becomes alive.

#include <chrono>   // for time durations
#include <iostream> // for printing to the screen
#include <thread>   // for pausing between generations
#include <vector>   // for the grid

// Size of the world and how long the simulation runs
const int ROWS = 20;
const int COLS = 40;
const int GENERATIONS = 100;
const int DELAY_MS = 150; // pause between frames, in milliseconds

// A Grid is a 2D table of true (alive) / false (dead) cells
using Grid = std::vector<std::vector<bool>>;

// Create an empty grid where every cell is dead
Grid makeEmptyGrid() {
    return Grid(ROWS, std::vector<bool>(COLS, false));
}

// Put a "glider" (a shape that walks across the grid) at the given position
void placeGlider(Grid& grid, int row, int col) {
    grid[row][col + 1] = true;
    grid[row + 1][col + 2] = true;
    grid[row + 2][col] = true;
    grid[row + 2][col + 1] = true;
    grid[row + 2][col + 2] = true;
}

// Put a "blinker" (3 cells in a row that flip between horizontal and vertical)
void placeBlinker(Grid& grid, int row, int col) {
    grid[row][col] = true;
    grid[row][col + 1] = true;
    grid[row][col + 2] = true;
}

// Count how many of the 8 surrounding cells are alive.
// The world "wraps around": walking off the right edge brings you to the left.
int countNeighbors(const Grid& grid, int row, int col) {
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) {
                continue; // skip the cell itself
            }
            int r = (row + dr + ROWS) % ROWS;
            int c = (col + dc + COLS) % COLS;
            if (grid[r][c]) {
                count++;
            }
        }
    }
    return count;
}

// Work out the next generation from the current one
Grid nextGeneration(const Grid& current) {
    Grid next = makeEmptyGrid();
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int neighbors = countNeighbors(current, r, c);
            if (current[r][c]) {
                next[r][c] = (neighbors == 2 || neighbors == 3);
            } else {
                next[r][c] = (neighbors == 3);
            }
        }
    }
    return next;
}

// Draw the grid in the terminal
void printGrid(const Grid& grid, int generation) {
    std::cout << "\033[2J\033[H"; // clear the screen and move cursor to top-left
    std::cout << "Conway's Game of Life - generation " << generation << "\n\n";
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            std::cout << (grid[r][c] ? "#" : ".");
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
}

int main() {
    Grid grid = makeEmptyGrid();

    // Starting pattern - try changing these or adding your own!
    placeGlider(grid, 1, 1);
    placeBlinker(grid, 10, 20);

    for (int gen = 0; gen < GENERATIONS; gen++) {
        printGrid(grid, gen);
        grid = nextGeneration(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
    }

    std::cout << "\nDone! Thanks for watching.\n";
    return 0;
}
