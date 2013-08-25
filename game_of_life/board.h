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
#include <tbb/tbb.h>

const int BOARD_WIDTH  = 25;
const int BOARD_HEIGHT = 25;

const int ALIVE = 1;
const int DEAD  = 0;

/**
 * \brief The grid for the celluar automata.
 *
 * This grid is hardcoded with the above height and width. Origin (0,0)
 * is top-left. Cells are contained in a 2-D array.
 */
class Board {

private:
    int _cells[BOARD_WIDTH][BOARD_HEIGHT] = {};

public:
    /**
     Retrieve the live/dead status of the given cell.
     @param x the x coordinate
     @param y the y coordinate
     @return 1 for alive, 0 for dead
     */
    int getCell(const int x, const int y) const;

    /**
     Look at all adjacent cells and count how many are 'alive'.

     @param x the x coordinate of the 'interesting' cell
     @param y the y coordinate of the 'interesting' cell
     @return the number of adjacent live cells
     */
    int getLiveNeighborCountForCell(const int x, const int y) const;

    /**
     Evolve a cell based on the number of live neighbors it has.

     @param curState whether the 'interesting' cell is alive or dead
     @param numLiveNeighbors how many adjacent cells are alive
     @return the new state (alive or dead) of the cell
     */
    int evolveCell(const int curState, const int numLiveNeigbors) const;

    /**
     Evolve a whole board one cycle.
     @param previousBoard holds the prior cycle's state so we can see what to do
     */
    void evolve(const Board &previousBoard);

    /**
     Randomize a board with an intial state.
     @param ratio approximately what number, out of 100, should be living
     */
    void randomize(const int ratio);

    /**
     Output a board state to console.
     */
    void print();
};

#endif /* defined(__game_of_life__board__) */
