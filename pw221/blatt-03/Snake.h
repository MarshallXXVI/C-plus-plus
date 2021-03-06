/* Copyright 2022 */
//  Snake.h
//  Clang
//
//  Created by Paramie Willmann on 11.05.22.
//

#ifndef SNAKE_H_
#define SNAKE_H_

// Global variables for position of the snake and direction.
extern int snakeRow;
extern int snakeCol;

// Global variables for snake's direction.
extern char direction;

// Global variables for snake's parts.
extern int tailRow[100], tailCol[100];
extern int nTail;

// Initialize the terminal for Snake.
void initTerminal();

// Draw a border.
void drawBorder();

// Initialize Snake.
void initSnake();

// Draw a Snake.
void drawSnake(bool mode);

// Logic for Snake's movement.
void moveSnake();

// handle if the key is pressed.
// if 'esc' is pressed then quit the game.
bool handleKey(int key);

// Calculate if Snake hits border, if true then game over.
bool collidesWithBorder();

// Calculate if snake hits its self, if true then game over.
bool collidesWithSelf();

#endif  // SNAKE_H_
