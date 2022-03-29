#ifndef COMMON__FUNC__H_
#define COMMON__FUNC__H_

#include <windows.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

/* SCREEN */
const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 512;
const int SCREEN_BPP = 32;
const int FRAME_PER_SECOND = 60;

/* TITLE */
const std::string WINDOW_TITLE = "Bounce Ball by Bui Minh Hoat";

/* COLOR KEY */

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

/* RENDER DRAW COLOR */
const int RENDER_DRAW_COLOR = 255;

/* TILE SIZE */
const int TILE_SIZE = 64;
const int TILE_LAYER = 1;
const int BLANK_TILE = 0;

/* MAP */
const int MAX_MAP_X = 400;
const int MAX_MAP_Y = 100;

typedef struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

typedef struct Map {
	int start_x_player_;
	int start_y_player_;
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int block[MAX_MAP_Y][MAX_MAP_X];

	const char* file_map;
};

enum TypeBlock {
	BLANK_TILES = 0,
	START_POINT = 1,
	GROUND_BLOCK = 2,
	THORN = 3,
	DYN_THORN = 4,
	CHECKPOINT = 5,
	RING_VERTICAL = 6,
	RING_HORIZONTAL = 7,
	END_POINT = 8,
	LIFE = 9,
};

#endif#pragma once
