// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>

#include <ncurses.h>
#include <unistd.h>
#include "./GameOfLife.h"

// Main function.
int main() {
  initTerminal();
  while (true) {
    MEVENT event;
    int key = getch();
    if (key == 'g') {
      putGlider(row, col);
      showState();
    } else if (key == 'G') {
      putGliderFactory(row, col);
      showState();
    }
    if (key == 27) break;
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        row = event.y;
        col = event.x / 2;
        setCell(row, col, true);
        showState();
        // mvprintw(1, 1, "Mouse clicked at %d,%d    \n", row, col);
        // refresh();
      }
    }
    usleep(50000);
  }
  endwin();
}
