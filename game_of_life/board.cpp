//
//  board.cpp
//  game_of_life
//
//  Created by Chris Powell on 8/24/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
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

int Board::evolveCell(const int curState, const int numLiveNeigbors) const {
    //TODO bounds checking

//    int state = _cells[x][y];
//    int numNeighbors = getLiveNeighborCountForCell(x, y);

    if (curState==ALIVE) {
        if (numLiveNeigbors < 2 || numLiveNeigbors > 3)
            return DEAD;
    } else {
        if (numLiveNeigbors == 3)
            return ALIVE;
    }
    return curState;
}

void Board::evolve(const Board &previousBoard) {
    for (int x=0; x<BOARD_WIDTH; ++x) {
        for (int y=0; y<BOARD_HEIGHT; ++y) {
            _cells[x][y] = evolveCell(previousBoard.getCell(x, y), previousBoard.getLiveNeighborCountForCell(x, y));
        }
    }
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
            std::cout << _cells[x][y];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}