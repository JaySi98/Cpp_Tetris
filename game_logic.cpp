#include "game_logic.h"


float calculateDelay(int level)
{
	return std::pow(0.8 - ((level - 1)*0.007), level - 1);
}


void checkKeyPressed(Tetrimino *current, Tetrimino *next, Tetrimino *hold, int board[][BOARD_HEIGHT], int* stats, bool* can_hold, int* keys)
{
	if (keys[LEFT]) 
	{
		if(checkHorizontal(current, board, -1))
			moveHorizontally(current, -1);
	}
		
	if (keys[RIGHT])
	{
		if (checkHorizontal(current, board, 1))
			moveHorizontally(current, 1);
	}

	if (keys[DOWN])
	{
		if (checkDown(current, board))
		{
			placeTetrimino(current, board);
			newTetrimino(current, next, stats, can_hold);
		}
		else
			moveDown(current);
	}
}


bool checkEndGame(int board[][BOARD_HEIGHT])
{
	for (int i = BOARD_HEIGHT - 1; i > TRUE_HEIGHT; i--)
		for (int j = 0; j < BOARD_WIDTH; j++)
			if (board[j][i]) 
				return false;

	return true;
}


void checkLines(int board[][BOARD_HEIGHT], int* total_score, int* req_score, int* lines)
{
	int k = 0;
	int l = 0;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		int count = 0;
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (board[j][i])
				count++;

			board[j][k] = board[j][i];
		}

		if (count < BOARD_WIDTH) k++;
		else if (count == BOARD_WIDTH) l++;
	}

	*lines += l;

	switch(l)
	{
		case 1: *total_score += 1; *req_score += 1; break;
		case 2: *total_score += 3; *req_score += 3; break;
		case 3: *total_score += 5; *req_score += 5; break; 
		case 4: *total_score += 8; *req_score += 8; break;
	}
}


void checkLevel(int* level, float* delay ,int* req_score)
{
	if (*req_score >= *level * 5)
	{
		*req_score = 0;

		if (*level < 20)
		{
			++*level;
			*delay = calculateDelay(*level);
		}
	}
}


