/* Copyright 2022 */
//  Snake.cpp
//  Clang
//
//  Created by Paramie Willmann on 11.05.22.
//

/* Implementation of Snake */

#include <ncurses.h>
#include "./Snake.h"

// _________________________________________________________________________
int snakeRow;
int snakeCol;
char direction;
int tailRow[100], tailCol[100];
int nTail;

// _________________________________________________________________________
void initTerminal() {
    initscr();
    curs_set(false);
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    start_color();
    noecho();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
}

// _________________________________________________________________________
void initSnake() {
    snakeRow = LINES / 2;
    snakeCol = COLS / 2;
    direction = 'r';
    nTail = 10;
}

// _________________________________________________________________________
void drawPixel(int y, int x) {
    mvprintw(y, x, " ");
}

// _________________________________________________________________________
void drawBorder() {
    attron(COLOR_PAIR(1));
    for (int row = 0; row < LINES; ++row) {
      for (int col = 0; col < COLS; ++col) {
        if (row == 0 || row == LINES - 1 || col <= 0 || col >= COLS - 1) {
          attron(A_REVERSE);
          mvprintw(row, col, " ");
          attroff(A_REVERSE);
        } else {
          mvprintw(row, col, " ");
        }
      }
    }
    attroff(COLOR_PAIR(1));
    refresh();
}

// _________________________________________________________________________
void drawSnake(bool mode) {
    attron(COLOR_PAIR(3));
    if (mode) attron(A_REVERSE);
    // mvprintw(snakeRow, snakeCol, " ");
    drawPixel(snakeRow, snakeCol);
    if (mode) attroff(A_REVERSE);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(2));
    if (mode) attron(A_REVERSE);
    for (int i = 0; i < nTail; i ++) {
        // mvprintw(tailRow[i], tailCol[i], " ");
        drawPixel(tailRow[i], tailCol[i]);
    }
    if (mode) attroff(A_REVERSE);
    attroff(COLOR_PAIR(2));
    refresh();
}

// _________________________________________________________________________
bool collidesWithBorder() {
    if (snakeRow == 0 || snakeRow == LINES ||
        snakeCol == 0 || snakeCol == COLS) {
        return true;
    }
    return false;
}

// _________________________________________________________________________
bool collidesWithSelf() {
    for (int i = 0; i < nTail; i++) {
        if (snakeRow == tailRow[i] && snakeCol == tailCol[i]) {
            return true;
        } else {
            continue;
        }
    }
    return false;
}

// _________________________________________________________________________
void moveSnake() {
    // Logic from C++ Tutorial 18 by NVitanovic 2015.
    int prevRow = tailRow[0];
    int prevCol = tailCol[0];
    int prev2Row, prev2Col;
    tailRow[0] = snakeRow;
    tailCol[0] = snakeCol;
    for (int i = 0; i < nTail; i++) {
        prev2Row = tailRow[i];
        prev2Col = tailCol[i];
        tailRow[i] = prevRow;
        tailCol[i] = prevCol;
        prevRow = prev2Row;
        prevCol = prev2Col;
    }
    //
    switch (direction) {
    case 'u':
        snakeRow--;
        break;
    case 'd':
        snakeRow++;
        break;
    case 'l':
        snakeCol--;
        break;
    case 'r':
        snakeCol++;
        break;
    default:
        break;
    }
}

// _________________________________________________________________________
bool handleKey(int key) {
    switch (key) {
    case KEY_UP:
        if (direction == 'd') {
            return false;
            break;
        }
        direction = 'u';
        return false;
        break;
    case KEY_DOWN:
        if (direction == 'u') {
            return false;
            break;
        }
        direction = 'd';
        return false;
        break;
    case KEY_LEFT:
        if (direction == 'r') {
            return false;
            break;
        }
        direction = 'l';
        return false;
        break;
    case KEY_RIGHT:
        if (direction == 'l') {
            return false;
            break;
        }
        direction = 'r';
        return false;
        break;
    case 27:
        return true;
        break;
    default:
        return false;
        break;
    }
}
