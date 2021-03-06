/* Copyright 2022 */
//  GameOfLife.cpp
//  Clang
//
//  Created by Paramie Willmann on 27.05.22.
//

#include <unistd.h>
#include "./GameOfLife.h"

// ____________________________________________________________________________
GameOfLife::GameOfLife(int row, int col) {
    cellsnow_ = &cells_;
    cellsnext_ = &nextcells_;
    stop_ = true;
    row_ = row;
    col_ = col;
}

// ____________________________________________________________________________
void GameOfLife::play(TerminalManager* terminalManager) {
    UserInput userInput;
    while (true) {
        showState(terminalManager);
        userInput = (*terminalManager).getUserInput();
        if (processUserInput(userInput)) break;
        if (stop_ == true) {
            continue;
        } else {
            updateState();
        }
        usleep(50000);
    }
    (*terminalManager).~TerminalManager();
}

// ____________________________________________________________________________
int GameOfLife::numAliveNeighbours(int row, int col) {
    int sum = 0;
    int RowRel[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int ColRel[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for (int i = 0; i < 8; ++i) {
        int y = (row + RowRel[i] + MAX_SIZE_) % MAX_SIZE_;
        int x = (col + ColRel[i] + MAX_SIZE_) % MAX_SIZE_;
        if ((*cellsnow_)[y][x]) {
            ++sum;
        }
    }
    return sum;
}

// ____________________________________________________________________________
void GameOfLife::updateState() {
    alive_ = 0;
    // von Musterlösung.
    bool (*tempCells)[MAX_SIZE_][MAX_SIZE_] = cellsnext_;
    cellsnext_ = cellsnow_;
    cellsnow_ = tempCells;

    for (int x = 0; x < MAX_SIZE_; ++x) {
        for (int y = 0; y < MAX_SIZE_; ++y) {
            int neighbours = numAliveNeighbours(x, y);
            (*cellsnext_)[x][y] = false;
            if ((*cellsnow_)[x][y]) {
            // Stay alive if 2 or 3 neighbours are alive, die otherwise.
            (*cellsnext_)[x][y] = neighbours > 1 && neighbours < 4;
            } else if (neighbours == 3) {
            // Birth of a cell if exactly 3 neighbours are alive.
            (*cellsnext_)[x][y] = true;
            }
        }
    }
}

// ____________________________________________________________________________
void GameOfLife::showState(TerminalManager* terminalManager) {
    alive_ = 0;
    for (int row = 0; row < MAX_SIZE_; ++row) {
        for (int col = 0; col < MAX_SIZE_; ++col) {
            if ((*cellsnext_)[row][col]) {
                alive_ = alive_ + 1;
                (*terminalManager).drawPixel(row, col, true, false);
            } else {
                (*terminalManager).drawPixel(row, col, false, false);
            }
        }
    }
    (*terminalManager).writeStr(true, alive_);
}
// ____________________________________________________________________________
bool GameOfLife::processUserInput(UserInput userInput) {
    if (userInput.isKeyQ()) {
        return true;
    }
    if (userInput.isKeyG()) {
        putGlider(row_, col_);
        return false;
    }
    if (userInput.isKeyS()) {
        updateState();
        return false;
    }
    if (userInput.isKeySpace()) {
        if (stop_) {
            stop_ = false;
        } else {
            stop_ = true;
        }
        return false;
    }
    if (userInput.isMouseClick()) {
        row_ = userInput.MouseRow_;
        col_ = userInput.MouseCol_;
        setCell(row_, col_, true);
        return false;
    }
    return false;
}

// ____________________________________________________________________________
void GameOfLife::putGlider(int row, int col) {
  int GLIDER_SIZE = 5;
  int gliderCoords[5][2] = { {0, 2}, {1, 0}, {1, 2}, {2, 1}, {2, 2} };
  setCell(row, col, false);
  setCell(row, col, true);
  for (int i = 0; i < GLIDER_SIZE; ++i) {
    setCell(row + gliderCoords[i][0], col + gliderCoords[i][1], false);
  }
}

// ____________________________________________________________________________
void GameOfLife::setCell(int row, int col, bool toggle) {
  if (row >= 0 && row < MAX_SIZE_ && col >= 0 && col < MAX_SIZE_) {
    (*cellsnext_)[row][col] = toggle ? !(*cellsnext_)[row][col] : true;
  }
}
