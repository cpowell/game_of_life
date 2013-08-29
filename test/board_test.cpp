//
//  board_test.cpp
//  game_of_life
//
//  Created by Chris Powell on 8/28/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"
#include "../include/board.h"

namespace {

    // The fixture for testing class Foo.
    class BoardTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body is empty.

        BoardTest() {
            // You can do set-up work for each test here.
        }

        virtual ~BoardTest() {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        virtual void SetUp() {
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        virtual void TearDown() {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        // Objects declared here can be used by all tests in the test case for Foo.
    };

    TEST(BoardTest, testEvolution)
    {

    }

    TEST(BoardTest, try_2)
    {
        EXPECT_EQ(2, 2);
    }

}
