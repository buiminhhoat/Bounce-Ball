#ifndef __COMMONFUNC__
#define __COMMONFUNC__

#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

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
const string ADDRESS_DATABASE = "Resources/database/database.txt";

/* BACKGROUND */
const int MAX_BACKGROUND = 8;

/* FONTS */
const int FONT_SIZE = 30;

/* GAME */
const int ORIGINAL_LIFE = 3;
const int EPS_PIXELS_IMPACT = 1;
const int MAX_ROW_SHOW = 5;
const int MAX_COL_SHOW = 10;
const int FIX_ZERO_INDEX = 5;
const int TIME_DELAY_GAMEOVER = 3000;
const int TIME_DELAY_POPBALL = 1000;
const int MS_ONE_SECOND = 1000;
const int INCREASE_LIFE = -1;
const int MAX_SIZE_SHOW_INFO = 15;
const int MAX_SHOW_LEADERBOARD = 5;

/* ... */
const int MID_POS_WIDTH = SCREEN_WIDTH / 2;
const int MID_POS_HEIGHT = SCREEN_HEIGHT / 2;
const double HALF_RATE = 0.5;
const int MAX_ONE_DIGIT = 9;
const int DISTANCE_UPPERCASE_VS_LOWERCASE = 32;
const int SMALLEST_TWO_DIGIT_NUMBER = 10;
const int MAX_SIZE_NAME_FILE = 100;


struct actionType {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool jump = false;
};

enum blockType {
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

enum lockType {
	LOCK = 0,
	UNLOCK = 1,
};
#endif 