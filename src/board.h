//
//  board.h
//  game_of_life
//
//  Created by Chris Powell on 8/24/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//  http://github.com/cpowell/game_of_life
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the source code.
//
#pragma once

const int BOARD_WIDTH = 150;
const int BOARD_HEIGHT = 150;

const int ALIVE = 1;
const int DEAD = 0;

/**
 * \brief The grid for the celluar automata.
 *
 * This grid is hardcoded with the above height and width. Origin (0,0)
 * is top-left. Cells are contained in a 2-D array.
 */
class Board {

private:
    //         ROWS          COLS
    int cells_[BOARD_HEIGHT][BOARD_WIDTH] = {};

public:
    int getCell(const int col, const int row) const;

    int getLiveNeighborCountForCell(const int col, const int row) const;

    int evolveCell(const int curState, const int numLiveNeighbors) const;

    void evolve(const Board& previousBoard);

    void randomize(const int ratio);

    void print() const;
};
