#include "Tetrimino.h"


void newTetrimino(Tetrimino *current, Tetrimino *next, int* stats, bool* can_hold)
{
	int n = next->shape - 1;

	current->shape = next->shape;
	current->tx = 3;
	current->ty = BOARD_HEIGHT - 1;

	stats[n]++;

	next->shape = std::rand() % 7 + 1;

	for (int i = 0; i < 4; i++)
	{
		current->pieces[i].x = piece[n][i] % 4;
		current->pieces[i].y = piece[n][i] / 4;

		next->pieces[i].x = piece[next->shape - 1][i] % 4;
		next->pieces[i].y = piece[next->shape - 1][i] / 4;
	}

	*can_hold = true;
}


void placeTetrimino(Tetrimino *current, int board[][BOARD_HEIGHT])
{
	for (int i = 0; i < 4; i++)
	{
		int pos_x = current->tx + current->pieces[i].x;
		int pos_y = current->ty - current->pieces[i].y;

		board[pos_x][pos_y] = current->shape; //1
	}
}


bool checkHorizontal(Tetrimino *current, int board[][BOARD_HEIGHT], int dx)
{
	for (int i = 0; i < 4; i++)
	{
		int pos_x = current->tx + current->pieces[i].x;
		int pos_y = current->ty - current->pieces[i].y;

		if (pos_x + dx < 0 || pos_x + dx >= BOARD_WIDTH || board[pos_x + dx][pos_y])
			return false;
	}

	return true;
}

void moveHorizontally(Tetrimino *current, int dx)
{
	current->tx += dx;
}

bool checkDown(Tetrimino *current, int board[][BOARD_HEIGHT])
{
	for (int i = 0; i < 4; i++)
	{
		int pos_x = current->tx + current->pieces[i].x;
		int pos_y = current->ty - current->pieces[i].y;

		if (pos_y == 0 || board[pos_x][pos_y - 1])
			return true;
	}

	return false;
}

void moveDown(Tetrimino *current)
{
	current->ty--;
}


void rotate(Tetrimino *current, int board[][BOARD_HEIGHT])
{
	Point old[4];
	for (int i = 0; i < 4; i++)
	{
		old[i] = current->pieces[i];

		int pos = 12 + current->pieces[i].y - (current->pieces[i].x * 4);

		current->pieces[i].x = pos % 4;
		current->pieces[i].y = pos / 4;
	}

	if (checkHorizontal(current, board, 0) == false)
	{
		if (checkHorizontal(current, board, 1))
		{
			moveHorizontally(current, 1);
		}
		else if (checkHorizontal(current, board, -1))
		{
			moveHorizontally(current, -1);
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				current->pieces[i] = old[i];
			}
		}
	}
}


void holdTetrimino(Tetrimino *current, Tetrimino *next, Tetrimino *hold, bool* can_hold, int* stats)
{
	if (hold->shape == -1)
	{
		hold->shape = current->shape;
		for (int i = 0; i < 4; i++)
		{
			hold->pieces[i].x = piece[hold->shape - 1][i] % 4;
			hold->pieces[i].y = piece[hold->shape - 1][i] / 4;
		}

		newTetrimino(current, next, stats, can_hold);

	}
	else if (*can_hold == true)
	{
		Tetrimino temp;
		temp.shape = hold->shape;

		hold->shape = current->shape;

		current->shape = temp.shape;

		for (int i = 0; i < 4; i++)
		{
			current->pieces[i].x = piece[current->shape - 1][i] % 4;
			current->pieces[i].y = piece[current->shape - 1][i] / 4;

			hold->pieces[i].x = piece[hold->shape - 1][i] % 4;
			hold->pieces[i].y = piece[hold->shape - 1][i] / 4;
		}

		current->tx = 3;
		current->ty = BOARD_HEIGHT - 1;

	}

	*can_hold = false;
}


void fastPlace(Tetrimino *current, Tetrimino *next, int board[][BOARD_HEIGHT], int* stats, bool* can_hold)
{
	while (!(checkDown(current, board)))
		moveDown(current);

	placeTetrimino(current, board);
	newTetrimino(current, next, stats, can_hold);
}

