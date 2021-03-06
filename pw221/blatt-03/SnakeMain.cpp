/* Copyright 2022 */
//  SnakeMain.cpp
//  Clang
//
//  Created by Paramie Willmann on 11.05.22.
//

#include <ncurses.h>
#include <unistd.h>
#include "./Snake.h"

// Drive Code for Snake
int main() {
    initTerminal();
    drawBorder();
    initSnake();
    drawSnake(true);
    // Loop forever untill game over.
    while (true) {
        if (collidesWithBorder()) {
            break;
        }
        if (collidesWithSelf()) {
            break;
        }
        // input from player.
        int key = getch();
        // check if "esc" is pressed.
        if (handleKey(key)) {
            break;
        } else {
            drawSnake(false);
            moveSnake();
            drawSnake(true);
            refresh();
        }
        usleep(100000);
    }
    // press 'esc' again to quit the terminal.
    while (true) {
        int key2 = getch();
        if (handleKey(key2)) {
            break;
        }
    }
    endwin();
}
