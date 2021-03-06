/* Copyright 2022 */
//  GameOfLife.cpp
//  Clang
//
//  Created by Paramie Willmann on 19.05.22.
//

#include <ncurses.h>
#include "./GameOfLife.h"

// ___________________________________________________________________________
bool cells[MAX_SIZE][MAX_SIZE] = {{ 0 }};
bool nextcells[MAX_SIZE][MAX_SIZE] = {{ 0 }};

// ___________________________________________________________________________
bool (*state)[MAX_SIZE][MAX_SIZE];
bool (*next)[MAX_SIZE][MAX_SIZE];

// ___________________________________________________________________________
int row;
int col;

// ___________________________________________________________________________
bool stop;
int update_steps = 0;
int living;

// ___________________________________________________________________________
void initTerminal() {
    initscr();              // Initializiation.
    cbreak();               // Don't wait for RETURN.
    noecho();               // Don't echo key presses on screen.
    curs_set(false);        // Don't show the cursor.
    nodelay(stdscr, true);  // Don't wait until key pressed.
    keypad(stdscr, true);   // For KEY_LEFT, KEY_UP, etc.

    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouseinterval(0);
}

// ___________________________________________________________________________
void initGame() {
    stop = true;
}

// ___________________________________________________________________________
void showState() {
    living = 0;
    for (int row = 0; row < MAX_SIZE; ++row) {
        for (int col = 0; col < MAX_SIZE; ++col) {
            if (cells[row][col]) {
                ++living;
                attron(A_REVERSE);
            }
            mvprintw(row, col * 2, "  ");
            if (cells[row][col]) attroff(A_REVERSE);
    }
  }
}

// ___________________________________________________________________________
int numAliveNeighbors(int row, int col) {
    int sum = 0;
    int RowRel[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int ColRel[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for (int i = 0; i < 8; ++i) {
        int y = (row + RowRel[i] + MAX_SIZE) % MAX_SIZE;
        int x = (col + ColRel[i] + MAX_SIZE) % MAX_SIZE;
        if (cells[y][x]) {
            ++sum;
        }
    }
    return sum;
}

// ___________________________________________________________________________
void updateState() {
    ++update_steps;
    for (int row = 0; row < MAX_SIZE; ++row) {
        for (int col =0; col < MAX_SIZE; ++col) {
            nextcells[row][col] = cells[row][col];
        }
    }
    next = &nextcells;
    for (int row = 0; row < MAX_SIZE; ++row) {
        for (int col = 0; col < MAX_SIZE; ++col) {
            int neighbors = numAliveNeighbors(row, col);
            state = &cells;
            int state_now = (*state)[row][col];
            if (state_now == 0 && neighbors == 3) {
                (*next)[row][col] = true;
            } else if (state_now == true && (neighbors < 2 || neighbors > 3)) {
                (*next)[row][col] = false;
            } else {
                (*next)[row][col] = state_now;
            }
        }
    }
    for (int row = 0; row < MAX_SIZE; ++row) {
        for (int col =0; col < MAX_SIZE; ++col) {
            cells[row][col] = nextcells[row][col];
        }
    }
}

// ___________________________________________________________________________
bool processUserInput(int keycode) {
    MEVENT event;
    if (keycode == 'q') {
        return true;
    }
    if (keycode == 'g') {
        putGlider(row, col);
        showState();
        return false;
    }
    if (keycode == ' ') {
        if (stop == true) {
            stop = false;
        } else if (stop == false) {
            stop = true;
        }
        return false;
    }
    if (keycode == 's') {
        updateState();
        showState();
    }
    if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_PRESSED) {
            row = event.y;
            col = event.x / 2;
            setCell(row, col, true);
            showState();
            return false;
        }
    }
    return false;
}

// ___________________________________________________________________________
void putGlider(int row, int col) {
  int GLIDER_SIZE = 5;
  int gliderCoords[5][2] = { {0, 2}, {1, 0}, {1, 2}, {2, 1}, {2, 2} };
  setCell(row, col, false);
  setCell(row, col, true);
  for (int i = 0; i < GLIDER_SIZE; ++i) {
    setCell(row + gliderCoords[i][0], col + gliderCoords[i][1], false);
  }
}

// ___________________________________________________________________________
void setCell(int row, int col, bool toggle) {
  if (row >= 0 && row < MAX_SIZE && col >= 0 && col < MAX_SIZE) {
    cells[row][col] = toggle ? !cells[row][col] : true;
  }
}
