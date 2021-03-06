// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>

#include <ncurses.h>
#include "./TerminalManager.h"

// ____________________________________________________________________________
bool UserInput::isKeySpace() { return keycode_ == ' '; }
bool UserInput::isKeyS() { return keycode_ == 's'; }
bool UserInput::isKeyQ() { return keycode_ == 'q'; }
bool UserInput::isKeyG() { return keycode_ == 'g'; }
bool UserInput::isMouseClick() {
  if (keycode_ == KEY_MOUSE) {
  MEVENT event;
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_PRESSED) {
            MouseRow_ = event.y;
            MouseCol_ = event.x / 2;
            return true;
        }
    }
  }
  return false;
}

// ____________________________________________________________________________
TerminalManager::TerminalManager() {
    initscr();              // Initializiation.
    cbreak();               // Don't wait for RETURN.
    noecho();               // Don't echo key presses on screen.
    curs_set(false);        // Don't show the cursor.
    nodelay(stdscr, true);  // Don't wait until key pressed.
    keypad(stdscr, true);   // For KEY_LEFT, KEY_UP, etc.

    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouseinterval(0);
}

// ____________________________________________________________________________
TerminalManager::~TerminalManager() {
  endwin();
}

// ____________________________________________________________________________
UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  return userInput;
}

// ____________________________________________________________________________
void TerminalManager::drawPixel(int row, int col,
                                bool inverse, bool useAlternativeColor) {
  if (inverse) attron(A_REVERSE);
  if (useAlternativeColor) attron(COLOR_PAIR(1));
  mvprintw(row, 2 * col, "  ");
  if (useAlternativeColor) attroff(COLOR_PAIR(1));
  if (inverse) attroff(A_REVERSE);
}

// ____________________________________________________________________________
void TerminalManager::refresh() {
  ::refresh();
}

// ____________________________________________________________________________
void TerminalManager::writeStr(bool inverse, int alive) {
  if (inverse) attron(A_REVERSE);
  mvprintw(0, 0, "alives : %d", alive);
  if (inverse) attroff(A_REVERSE);
}
