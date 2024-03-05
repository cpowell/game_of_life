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

#include <iostream>
#include <tbb/tbb.h>

int Board::getCell(const int col, const int row) const {
    return _cells[row][col];
}

int Board::getLiveNeighborCountForCell(const int col, const int row) const {
    int above = row - 1;
    if (above < 0)
        above = BOARD_HEIGHT;

    int below = row + 1;
    if (below >= BOARD_HEIGHT)
        below = 0;

    int left = col - 1;
    if (left < 0)
        left = BOARD_WIDTH;

    int right = col + 1;
    if (right >= BOARD_WIDTH) {
        right = 0;
    }

    int live = 0;
    for (int dcol = left; dcol <= right; ++dcol) {
        for (int drow = above; drow <= below; ++drow) {
            if (dcol == col && drow == row)
                continue;

            live += _cells[drow][dcol];
        }
    }
    return live;
}

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
//            _cells[row][col] = evolveCell(previousBoard.getCell(col, row), previousBoard.getLiveNeighborCountForCell(col, row));
//        }
//    }
//}

// Multithreaded TBB version (example):
void Board::evolve(const Board& previousBoard) {
    // The lambda doesn't need to be defined separately like this;
    // this is just to help readability.
    auto lambda = [&](int row) {
        for (int col = 0; col < BOARD_WIDTH; ++col) {
            _cells[row][col] = evolveCell(previousBoard.getCell(col, row), previousBoard.getLiveNeighborCountForCell(col, row));
        }
    };
    tbb::parallel_for(0, BOARD_HEIGHT, lambda);
}

void Board::randomize(const int ratio) {
    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        for (int col = 0; col < BOARD_WIDTH; ++col) {
            if (rand() % 100 < ratio)
                _cells[row][col] = 1;
        }
        std::cout << std::endl;
    }
}

void Board::print() {
    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        for (int col = 0; col < BOARD_WIDTH; ++col) {
            if (_cells[row][col] == 1)
                std::cout << "*";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}