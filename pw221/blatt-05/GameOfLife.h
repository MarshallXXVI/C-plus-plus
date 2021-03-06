/* Copyright 2022 */
//  GameOfLife.h
//  Clang
//
//  Created by Paramie Willmann on 27.05.22.
//

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <gtest/gtest.h>
#include "./TerminalManager.h"

// initialize Game Of Life.
class GameOfLife {
 public:
        // Initialize the game.
        GameOfLife(int row, int col);
        FRIEND_TEST(GameOfLifeTest, constructor);

        // Play the game.
        void play(TerminalManager* terminalManager);

 private:
        // max_size fixed
        static const int MAX_SIZE_ = 250;

        // create current field all elements are 0.
        bool cells_[MAX_SIZE_][MAX_SIZE_] = {{0}};
        bool (*cellsnow_)[MAX_SIZE_][MAX_SIZE_];

        // create next field all elements are 0.
        bool nextcells_[MAX_SIZE_][MAX_SIZE_] = {{0}};
        bool (*cellsnext_)[MAX_SIZE_][MAX_SIZE_];

        // current position of Logic.
        int row_;
        int col_;
        int alive_;

        // start the game with stop as default.
        bool stop_ = true;

        // count how many neighbors are alive.
        int numAliveNeighbours(int row, int col);

        // Compute for updates next state.
        void updateState();

        // Show state.
        void showState(TerminalManager* terminalManager);

        // User input.
        bool processUserInput(UserInput userInput);

        // Put a "glider" at the given position.
        void putGlider(int row, int col);

        // Set the state of the given cell to "alive".
        // If "toggle", invert the state.
        void setCell(int row, int col, bool toggle);
};

#endif  // GAMEOFLIFE_H_
