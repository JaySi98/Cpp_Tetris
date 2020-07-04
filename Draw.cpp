#include "Draw.h"

void drawStats(sf::RenderWindow &window, sf::Text* text, int score, int level, int lines)
{
	text->setPosition(522, 94);
	text->setString(std::to_string(score));
	window.draw(*text);

	text->setPosition(522, 129);
	text->setString(std::to_string(level));
	window.draw(*text);

	text->setPosition(522, 164);
	text->setString(std::to_string(lines));
	window.draw(*text);
}


void drawStatistics(sf::RenderWindow &window, sf::Text* text, int* stats)
{
	for (int i = 0; i < TILES; i++)
	{
		text->setPosition(522, 366 + 41 * i);
		text->setString(std::to_string(stats[i]));
		window.draw(*text);
	}
}

void drawTime(sf::RenderWindow &window, sf::Text* text, sf::Clock* clock)
{
	int min = (int)clock->getElapsedTime().asSeconds() / 60;
	int sec = (int)clock->getElapsedTime().asSeconds() % 60;

	text->setString(std::to_string(min));
	if (min >= 10)
		text->setPosition(498, 199);
	else
		text->setPosition(522, 199);
	window.draw(*text);

	text->setString(std::to_string(sec));
	text->setPosition(567, 199);
	window.draw(*text);
}

void drawTetrimino(sf::RenderWindow &window, sf::Sprite &spr_tile, Tetrimino *current)
{
	int color = (current->shape - 1) * TILE_SIZE;
	spr_tile.setTextureRect(sf::IntRect(color, 0, TILE_SIZE, TILE_SIZE));

	for (int i = 0; i < 4; i++)
	{
		int pos_x = current->tx + current->pieces[i].x;
		int pos_y = current->ty - current->pieces[i].y;

		if (pos_y <= TRUE_HEIGHT)
		{
			spr_tile.setPosition((pos_x * TILE_SIZE) + OFFSET, ((TRUE_HEIGHT - pos_y) * TILE_SIZE) + OFFSET);
			window.draw(spr_tile);
		}
	}
}


void drawMinis(sf::RenderWindow &window, sf::Sprite &spr_mini, Tetrimino *next, Tetrimino *hold)
{
	int color = (next->shape - 1)  * TILE_MINI;
	spr_mini.setTextureRect(sf::IntRect(color, 0, TILE_MINI, TILE_MINI));

	for (int i = 0; i < 4; i++)
	{
		int pos_x = next->tx + (next->pieces[i].x * TILE_MINI);
		int pos_y = next->ty + (next->pieces[i].y * TILE_MINI);

		spr_mini.setPosition(pos_x, pos_y);
		window.draw(spr_mini);
	}

	if (hold->shape != -1)
	{
		color = (hold->shape - 1) * TILE_MINI; //bez inta
		spr_mini.setTextureRect(sf::IntRect(color, 0, TILE_MINI, TILE_MINI));

		for (int i = 0; i < 4; i++)
		{
			int pos_x = hold->tx + (hold->pieces[i].x * TILE_MINI);
			int pos_y = hold->ty + (hold->pieces[i].y * TILE_MINI);

			spr_mini.setPosition(pos_x, pos_y);
			window.draw(spr_mini);
		}
	}
}


void drawBoard(sf::RenderWindow &window, sf::Sprite &spr_tile, int board[][BOARD_HEIGHT])
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j <= TRUE_HEIGHT; j++)
		{
			if (board[i][j])
			{
				int color = (board[i][j] - 1) * TILE_SIZE;

				spr_tile.setTextureRect(sf::IntRect(color, 0, TILE_SIZE, TILE_SIZE));
				spr_tile.setPosition(i * TILE_SIZE + OFFSET, (TRUE_HEIGHT - j) * TILE_SIZE + OFFSET);
				window.draw(spr_tile);
			}
		}
	}
}

