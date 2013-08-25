//
//  main.cpp
//  game_of_life
//
//  Created by Chris Powell on 8/24/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "board.h"

// Forward declaration
void swapBoards(Board&, Board&);

int main(int argc, const char * argv[]) {

    // There are two boards defined; the one "in back" is updated based
    // on the current status of the one "in front", then brought to the
    // front. Efficient, and kind to memory.
    Board flip, flop;

    // Seed the RNG and set up a random smattering of live cells.
    srand((unsigned int) time(NULL));
    flip.randomize(20);

    while (true) {
        flop.evolve(flip);
        flop.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
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

