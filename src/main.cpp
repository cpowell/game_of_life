//
//  main.cpp
//  game_of_life
//
//  Created by Chris Powell on 8/24/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//  http://github.com/cpowell/game_of_life
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the source code.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "board.h"

// Forward declaration
void swapBoards(Board&, Board&);

int main() {
    // There are two boards defined; the one "in back" is updated based
    // on the current status of the one "in front", then brought to the
    // front. Efficient, and kind to memory.
    Board flip, flop;

    // Seed the RNG and set up a random smattering of live cells.
    srand((unsigned int) time(NULL));
    flip.randomize(20);

    // This routine evolves and prints the board forever; you must
    // terminate the program.
    while (true) {
        flop.evolve(flip);

        // To see the Intel TBB parallelism at work, comment out these
        // next two lines to let the program run unfettered. It will
        // maximize your available cores.
        flop.print();
        // std::this_thread::sleep_for(std::chrono::milliseconds(150));

        swapBoards(flip, flop);
    }

    return 0;
}

/**
 A textbook 'swap' function using pass-by-reference.
 @param one is a reference to the first board
 @param two is a reference to the second board
 */
void swapBoards(Board &one, Board &two) {
    Board temp = one;
    one = two;
    two = temp;
}

