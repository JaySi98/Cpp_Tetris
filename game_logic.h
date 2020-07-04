#pragma once
#include <SFML/Graphics.hpp>
#include "global_var.h"
#include "Tetrimino.h"
#include <time.h>
#include <cstdlib>
#include <math.h>

float calculateDelay(int level);
void checkKeyPressed(Tetrimino *current, Tetrimino *next, Tetrimino *hold, int board[][BOARD_HEIGHT], int* stats, bool* can_hold, int* keys);
void checkLines(int board[][BOARD_HEIGHT], int* total_score, int* req_score, int* lines);
void checkLevel(int* level, float* delay, int* req_score);
bool checkEndGame(int board[][BOARD_HEIGHT]);
