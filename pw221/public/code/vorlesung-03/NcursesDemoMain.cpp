// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>

#include <ncurses.h>
#include <unistd.h>
#include "./NcursesDemo.h"

int main() {
  initTerminal();
  // attron(COLOR_PAIR(1));
  // mvprintw(10, 50, "Doof");
  // attroff(COLOR_PAIR(1));
  drawBorder();
  boxRow = LINES / 2;
  boxCol = COLS / 2;
  drawBox(true);
  // Loop for a certain time and ask or user input in discrete time steps.
  for (int timeStep = 1; timeStep <= 10000; ++timeStep) {
    int i = 0;
    while (getch() != -1) ++i;
    mvprintw(0, 0, "%d", i);
    /*
    int keycode = getch();
    if (keycode != -1 || true) {
      drawBox(false);
      attron(COLOR_PAIR(2));
      mvprintw(2, 4, "%d    ", keycode);
      attroff(COLOR_PAIR(2));
      switch (keycode) {
        case KEY_LEFT:
          boxCol = boxCol - 1;
          break;
        case KEY_RIGHT:
          boxCol = boxCol + 1;
          break;
      }
      drawBox(true);
      refresh();
    }
    */
    usleep(1000 * 500);
  }
  endwin();
}
