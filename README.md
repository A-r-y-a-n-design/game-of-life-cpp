# Conway's Game of Life (C++)

A simple console version of Conway's Game of Life, written in C++ as my Day 1 project while learning the language.

## The rules
1. A live cell with 2 or 3 live neighbors stays alive.
2. A live cell with any other number of neighbors dies.
3. A dead cell with exactly 3 live neighbors becomes alive.

## Build and run

```bash
g++ -std=c++17 -o life main.cpp
./life          # on Windows: life.exe
```

You need a C++ compiler such as g++ (Linux/macOS/MinGW) or clang++. The simulation runs for 100 generations; `#` is a live cell and `.` is a dead one.

## Things to try
- Change `ROWS`, `COLS`, `GENERATIONS`, or `DELAY_MS` at the top of `main.cpp`.
- Add your own starting patterns in `main()`.
