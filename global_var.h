#pragma once

//********** GENERAL *********//
#define MAX_FPS 27	//60
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 22
#define TRUE_HEIGHT 19
#define OFFSET 18
#define DOWN 2
#define LEFT 0
#define RIGHT 1

//********** TILES *********//
#define TILE_SIZE 32
#define TILE_MINI 17
#define TILES 7

//********** FONT AND TEXT LOCATION *********//
#define FONT_SIZE 22 //14


static int piece[7][4] = {
   8,  9,  10,  11,	//I
   5,  6,  9, 10,	//O
   4,  5,  9, 10,	//Z
   6,  7,  9, 10,	//S
   7, 11, 10,  9,	//L
   4,  8,  9, 10,	//J
   6,  9,  10, 11	//T
};


struct Point
{
	int x;
	int y;
};


struct Tetrimino
{
	Point pieces[4];
	int tx;
	int ty;

	int shape;
};