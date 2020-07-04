#pragma once
#include <SFML/Graphics.hpp>
#include "global_var.h"
#include "game_logic.h"
#include <time.h>
#include <cstdlib>

void newTetrimino(Tetrimino *current, Tetrimino *next, int* stats, bool* can_hold);
void placeTetrimino(Tetrimino *current, int board[][BOARD_HEIGHT]);
void holdTetrimino(Tetrimino *current, Tetrimino *next, Tetrimino *hold, bool* can_hold, int* stats);
void fastPlace(Tetrimino *current, Tetrimino *next, int board[][BOARD_HEIGHT], int* stats, bool* can_hold);

void rotate(Tetrimino *current, int board[][BOARD_HEIGHT]);

bool checkHorizontal(Tetrimino *current, int board[][BOARD_HEIGHT], int dx);
void moveHorizontally(Tetrimino *current, int dx);

bool checkDown(Tetrimino *current, int board[][BOARD_HEIGHT]);
void moveDown(Tetrimino *current);