#ifndef __COMMONFUNC__
#define __COMMONFUNC__

#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

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

/* RENDER DRAW COLOR */
const int RENDER_DRAW_COLOR = 255;

/* TILE SIZE */
const int TILE_SIZE = 64;
const int TILE_LAYER = 1;

/* MAP */
const int MAX_MAP_X = 700;
const int MAX_MAP_Y = 50;

/* LEVEL */
const int MAX_LEVEL = 50;

/* DATABASE */
const string ADDRESS_DATABASE = "database//database.txt";

/* GAME */
const int ORIGINAL_LIFE = 3;
const int EPS_PIXELS_IMPACT = 1;

struct Input {
	bool left = 0;
	bool right = 0;
	bool up = 0;
	bool down = 0;
	bool jump = 0;
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
	ENDPOINT = 8,
	LIFE = 9,
};

enum TypeLevel {
	LOCK = 0,
	UNLOCK = 1,
};
#endif 