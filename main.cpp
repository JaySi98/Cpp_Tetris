#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "game_logic.h"
#include "Tetrimino.h"
#include "Draw.h"

//============================================= MAIN =============================================//
int main()
{
	//********** CREATING ALL INSTANCES *********//

	//CREATING WINDOW INSTANCE
	sf::RenderWindow window(sf::VideoMode(636, 676), "Tetris");
	//window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(MAX_FPS);

	//CREATING TILE'S TEXTURE
	sf::Texture txr_tile;
	txr_tile.loadFromFile("../textures/tiles.png");
	sf::Sprite spr_tile(txr_tile);
	spr_tile.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));

	//CREATING MENU TILE'S TEXTURE
	sf::Texture txr_mini;
	txr_mini.loadFromFile("../textures/tiles_mini.png");
	sf::Sprite spr_mini(txr_mini);
	spr_mini.setTextureRect(sf::IntRect(0,0,TILE_MINI, TILE_MINI));

	//LOADING BACKGROUND'S SPRITE
	sf::Texture txr_back;
	txr_back.loadFromFile("../textures/background_2.png");
	sf::Sprite spr_back(txr_back);

	//LOADING FONT 
	sf::Font font;
	font.loadFromFile("../textures/font.ttf");
	
	//CREATING TEXT INSTANCE
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(FONT_SIZE);

	//CLOCK INSTANCES
	sf::Clock clock;								// for counting ticks
	sf::Clock normal_clock;							// for time passed
	
	//RANDOM SEED
	std::srand(std::time(NULL));


	//********** GAME VARIABLES *********//
	
	int board[BOARD_WIDTH][BOARD_HEIGHT] = { 0 };	//array for holding tiles position 

	int level = 1;									// current level
	int lines = 0;									// lines cleared
	int total_score = 0;							// gained points 
	int req_score = 0;								// points required for next level
	int statistics[7] = { 0 };						// array holding how many given shape was placed

	float timer = 0;								// for holding time passed since last tick
	float delay = calculateDelay(level);			// time beetween each tick based on current level

	int keys_states[3] = { 0 };						// for holding witch key is currently pressed

	//TETRIMINOS
	Tetrimino next;									//displays next shape  									
	next.shape = std::rand() % 7 + 1;
	next.tx = 505; next.ty = 241;

	Tetrimino hold;									//displays shape held by pressing "C"
	hold.shape = -1;
	hold.tx = 505; hold.ty = 284;
	bool can_hold = true;

	Tetrimino current;								//displays currently controled shape 
	newTetrimino(&current, &next, statistics, &can_hold);



	//********** GAME LOOP *********//
	
	while (window.isOpen() && checkEndGame(board))
	{
		float time = clock.restart().asSeconds();
		timer += time;


		//********** CHECKING EVENTS *********//
		sf::Event event;
		while (window.pollEvent(event))
		{
			//CLOSING WINDOW
			if (event.type == sf::Event::Closed)			
				window.close();

			//PRESSING KEY
			else if (event.type == sf::Event::KeyPressed)	
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Left:	keys_states[LEFT] = 1; break;
					case sf::Keyboard::Right:	keys_states[RIGHT] = 1; break;
					case sf::Keyboard::Down:	keys_states[DOWN] = 1; break;

					case sf::Keyboard::Up: rotate(&current, board); break;					// rotating current tetrimono
					
					case sf::Keyboard::C:													// taking current tetrimino to hold
					{
						holdTetrimino(&current, &next, &hold, &can_hold, statistics);

						break;
					}

					case sf::Keyboard::Space:												// instant placing current tetrimino
					{
						fastPlace(&current, &next, board, statistics, &can_hold);

						break;
					}
				}
			}
			
			//RELEASING KEY
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Left:	keys_states[LEFT] = 0; break;
					case sf::Keyboard::Right:	keys_states[RIGHT] = 0; break;
					case sf::Keyboard::Down:	keys_states[DOWN] = 0; break;
				}
			}
		}


		//********** TICK EVENTS *********//
		
		if (timer > delay)									// when mesured time reached current delay 
		{
			if (checkDown(&current, board))					// moving curent tetrimino one down 
			{
				placeTetrimino(&current, board);
				newTetrimino(&current, &next, statistics, &can_hold);
			}
			else
				moveDown(&current);

			timer = 0;
		}


		//********** CHECKING STUFF *********//
		checkKeyPressed(&current, &next, &hold, board, statistics, &can_hold, keys_states);	// checking if keys are pressed
		checkLines(board, &total_score, &req_score, &lines);								// checking if there are filled horizontal lines
		checkLevel(&level, &delay, &req_score);												// checking if reached next level


		//********** DRAWING *********//
		
		window.clear();								
		window.draw(spr_back);									// drawing background
		drawTetrimino(window, spr_tile, &current);				// drawing current tetrimino
		drawBoard(window, spr_tile, board);						// drawing placed tiles
		drawStats(window, &text, total_score, level, lines);	// printing current level and cleared lines
		drawStatistics(window, &text, statistics);				// printing stats
		drawTime(window, &text, &normal_clock);					// printing passed time
		drawMinis(window, spr_mini, &next, &hold);				// drawing next and hold tetrimino
		window.display();
	}


	system("pause");
	return 0;
}