#pragma once
#include <SFML/Graphics.hpp>
#include "global_var.h"
#include "Tetrimino.h"
#include <time.h>
#include <cstdlib>

void drawStats(sf::RenderWindow &window, sf::Text* text, int score, int level, int lines);
void drawStatistics(sf::RenderWindow &window, sf::Text* text, int* stats);
void drawTime(sf::RenderWindow &window, sf::Text* text, sf::Clock* clock);
void drawTetrimino(sf::RenderWindow &window, sf::Sprite &spr_tile, Tetrimino *current);
void drawMinis(sf::RenderWindow &window, sf::Sprite &spr_mini, Tetrimino *next, Tetrimino *hold);
void drawBoard(sf::RenderWindow &window, sf::Sprite &spr_tile, int board[][BOARD_HEIGHT]);