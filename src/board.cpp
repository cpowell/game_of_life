//
//  board.cpp
//  game_of_life
//
//  Created by Chris Powell on 8/24/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//  http://github.com/cpowell/game_of_life
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the source code.
//

#include "board.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tbb/tbb.h>

/// Retrieve the live/dead status of the given cell.
/// @param col the y coordinate
/// @param row the x coordinate
/// @return 1 for alive, 0 for dead
int Board::getCell(const int col, const int row) const {
    return cells_[row][col];
}

/// Look at all adjacent cells and count how many are 'alive'.
/// @param col the y coordinate of the 'interesting' cell
/// @param row the x coordinate of the 'interesting' cell
/// @return the number of adjacent live cells
int Board::getLiveNeighborCountForCell(const int col, const int row) const {
    int above = std::clamp(row - 1, 0, BOARD_HEIGHT);
    int below = std::clamp(row + 1, 0, BOARD_HEIGHT);
    int left = std::clamp(col - 1, 0, BOARD_WIDTH);
    int right = std::clamp(col + 1, 0, BOARD_WIDTH);

    int live = 0;
    for (int drow = above; drow <= below; ++drow) {
        for (int dcol = left; dcol <= right; ++dcol) {
            if (drow == row && dcol == col)
                continue;

            live += cells_[drow][dcol];
        }
    }
    return live;
}

/// Evolve a cell based on the number of live neighbors it has.
/// @param curState whether the 'interesting' cell is alive or dead
/// @param numLiveNeighbors how many adjacent cells are alive
/// @return the new state (alive or dead) of the cell
int Board::evolveCell(const int curState, const int numLiveNeighbors) const {
    if (curState == ALIVE) {
        if (numLiveNeighbors < 2 || numLiveNeighbors > 3)
            return DEAD;
    } else {
        if (numLiveNeighbors == 3)
            return ALIVE;
    }
    return curState;
}

// Single-threaded, original version:
//void Board::evolve(const Board& previousBoard) {
//    for (int col = 0; col < BOARD_WIDTH; ++col) {
//        for (int row = 0; row < BOARD_HEIGHT; ++row) {
//            cells_[row][col] = evolveCell(previousBoard.getCell(col, row), previousBoard.getLiveNeighborCountForCell(col, row));
//        }
//    }
//}

/// Evolve a whole board one cycle.
/// @param previousBoard holds the prior cycle's state so we can see what to do
void Board::evolve(const Board& previousBoard) {
    // The lambda doesn't need to be defined separately like this;
    // this is just to help readability.
    auto lambda = [&](int row) {
        for (int col = 0; col < BOARD_WIDTH; ++col) {
            cells_[row][col] = evolveCell(previousBoard.getCell(col, row), previousBoard.getLiveNeighborCountForCell(col, row));
        }
        };
    tbb::parallel_for(0, BOARD_HEIGHT, lambda);
}

/// Randomize a board with an intial state.
/// @param ratio approximately what number, out of 100, should be living
void Board::randomize(const int ratio) {
    for (auto& row : cells_) {
        for (int& cell : row) {
            if (rand() % 100 < ratio)
                cell = ALIVE;
        }
    }
}

/// Output a board state to console.
void Board::print() const {
    for (const auto& row : cells_) {
        for (int cell : row) {
            if (cell == ALIVE)
                std::cout << "O";
            else
                std::cout << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}