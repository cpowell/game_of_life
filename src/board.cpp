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

int Board::getCell(const int x, const int y) const {
    return _cells[x][y];
}

int Board::getLiveNeighborCountForCell(const int x, const int y) const {
    int above = y-1;
    if (above < 0)
        above = BOARD_HEIGHT;

    int below = y+1;
    if (below >= BOARD_HEIGHT)
        below = 0;

    int left = x-1;
    if (left < 0)
        left = BOARD_WIDTH;

    int right = x+1;
    if (right >= BOARD_WIDTH) {
        right = 0;
    }

    int live = 0;
    for (int xx=left; xx<=right; ++xx) {
        for (int yy=above; yy<=below; ++yy) {
            if (xx==x && yy==y)
                continue;

            live += _cells[xx][yy];
        }
    }
    return live;
}

int Board::evolveCell(const int curState, const int numLiveNeighbors) const {
    if (curState==ALIVE) {
        if (numLiveNeighbors < 2 || numLiveNeighbors > 3)
            return DEAD;
    } else {
        if (numLiveNeighbors == 3)
            return ALIVE;
    }
    return curState;
}

// Single-threaded, original version:
//void Board::evolve(const Board &previousBoard) {
//    for (int x=0; x<BOARD_WIDTH; ++x) {
//        for (int y=0; y<BOARD_HEIGHT; ++y) {
//            _cells[x][y] = evolveCell(previousBoard.getCell(x, y), previousBoard.getLiveNeighborCountForCell(x, y));
//        }
//    }
//}

// Multithreaded TBB version (example):
void Board::evolve(const Board &previousBoard) {
    // The lambda doesn't need to be defined separately like this;
    // this is just to help readability.
    auto lambda = [&](int x) {
        for (int y=0; y<BOARD_HEIGHT; ++y) {
            _cells[x][y] = evolveCell(previousBoard.getCell(x, y), previousBoard.getLiveNeighborCountForCell(x, y));
        }
    };

    tbb::parallel_for(0, BOARD_WIDTH, lambda);
}

void Board::randomize(const int ratio) {
    for (int y=0; y<BOARD_HEIGHT; ++y) {
        for (int x=0; x<BOARD_WIDTH; ++x) {
            if (rand() % 100 < ratio)
                _cells[x][y]=1;
        }
        std::cout << std::endl;
    }
}

void Board::print() {
    for (int y=0; y<BOARD_HEIGHT; ++y) {
        for (int x=0; x<BOARD_WIDTH; ++x) {
            if (_cells[x][y]==1)
                std::cout<< "*";
            else
                std::cout<< " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}