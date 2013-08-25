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

void swapBoards(Board &one, Board &two) {
    Board temp = one;
    one = two;
    two = temp;
}

int main(int argc, const char * argv[]) {

    Board flip, flop;

    srand(time(NULL));
    flip.randomize(20);

//    for (int c=0; c<300000; ++c) {
    while (true) {
        flop.evolve(flip);
        flop.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        swapBoards(flip, flop);
    }

    return 0;
}

