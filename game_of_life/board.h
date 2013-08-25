//
//  board.h
//  game_of_life
//
//  Created by Chris Powell on 8/24/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#ifndef __game_of_life__board__
#define __game_of_life__board__

#include <iostream>

const int BOARD_WIDTH  = 15;
const int BOARD_HEIGHT = 15;

const int ALIVE = 1;
const int DEAD  = 0;

class Board {

private:
    int _cells[BOARD_WIDTH][BOARD_HEIGHT] = {};

public:
    int getCell(const int x, const int y) const;
    int getLiveNeighborCountForCell(const int x, const int y) const;
    int evolveCell(const int curState, const int numLiveNeigbors) const;
    void evolve(const Board &previousBoard);
    void randomize(const int ratio);
    void print();
};

#endif /* defined(__game_of_life__board__) */
