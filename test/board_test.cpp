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

        // Objects declared here can be used by all tests in the test case for Board.
        Board b;
    };

    TEST_F(BoardTest, testDeadCellShouldStayDeadForNotThreeNeighbors)
    {
        int ret = b.evolveCell(0, 0);
        EXPECT_EQ(0, ret);

        ret = b.evolveCell(0, 1);
        EXPECT_EQ(0, ret);

        ret = b.evolveCell(0, 2);
        EXPECT_EQ(0, ret);

        ret = b.evolveCell(0, 4);
        EXPECT_EQ(0, ret);

        ret = b.evolveCell(0, 5);
        EXPECT_EQ(0, ret);

        ret = b.evolveCell(0, 6);
        EXPECT_EQ(0, ret);

        ret = b.evolveCell(0, 7);
        EXPECT_EQ(0, ret);

        ret = b.evolveCell(0, 8);
        EXPECT_EQ(0, ret);
    }

    TEST_F(BoardTest, testDeadCellComesAliveWithThreeNeighbors)
    {
        int val = b.evolveCell(0,3);
        EXPECT_EQ(1, val);
    }

    TEST_F(BoardTest, testLiveCellDiesWithNotThreeNeighbors)
    {
        int val = b.evolveCell(0, 0);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 1);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 2);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 4);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 5);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 6);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 7);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 8);
        EXPECT_EQ(0, val);

        val = b.evolveCell(0, 9);
        EXPECT_EQ(0, val);
    }

    TEST_F(BoardTest, testLiveCellStaysAliveWithThreeNeighbors)
    {
        int val = b.evolveCell(1, 3);
        EXPECT_EQ(1, val);
    }

}
