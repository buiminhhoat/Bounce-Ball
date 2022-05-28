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

/* ADDRESS */
const string ADDRESS_BACKGROUND = "Resources/Image/background/background";
const string ADDRESS_LOGO_SMALL = "Resources/Image/logo/logo_small.png";
const string ADDRESS_LOGO = "Resources/Image/logo/logo.png";
const string ADDRESS_MENU_PLAY_BUTTON = "Resources/Image/button/menu_button_play.png";
const string ADDRESS_MENU_PLAY_BUTTON_CLICK = "Resources/Image/button/menu_button_play_click.png";
const string ADDRESS_MENU_LEADERBOARD_BUTTON = "Resources/Image/button/menu_button_leaderboard.png";
const string ADDRESS_MENU_LEADERBOARD_BUTTON_CLICK = "Resources/Image/button/menu_button_leaderboard_click.png";
const string ADDRESS_MENU_HOWTOPLAY_BUTTON = "Resources/Image/button/menu_button_howtoplay.png";
const string ADDRESS_MENU_HOWTOPLAY_BUTTON_CLICK = "Resources/Image/button/menu_button_howtoplay_click.png";
const string ADDRESS_MENU_SETTINGS_BUTTON = "Resources/Image/button/menu_button_settings.png";
const string ADDRESS_MENU_SETTINGS_BUTTON_CLICK = "Resources/Image/button/menu_button_settings_click.png";
const string ADDRESS_MENU_REGISTER_BUTTON = "Resources/Image/button/menu_button_register.png";
const string ADDRESS_MENU_REGISTER_BUTTON_CLICK = "Resources/Image/button/menu_button_register_click.png";
const string ADDRESS_MENU_LOGIN_BUTTON = "Resources/Image/button/menu_button_login.png";
const string ADDRESS_MENU_LOGIN_BUTTON_CLICK = "Resources/Image/button/menu_button_login_click.png";
const string ADDRESS_MENU_LOGOUT_BUTTON = "Resources/Image/button/menu_button_logout.png";
const string ADDRESS_MENU_LOGOUT_BUTTON_CLICK = "Resources/Image/button/menu_button_logout_click.png";
const string ADDRESS_MENU_BACK_BUTTON = "Resources/Image/button/back_button.png";
const string ADDRESS_MENU_BACK_BUTTON_CLICK = "Resources/Image/button/back_button_click.png";
const string ADDRESS_SELECT_LEVEL = "Resources/Image/level/select_level.png";
const string ADDRESS_SELECT_LEVEL_LOCKED = "Resources/Image/level/select_level_locked.png";
const string ADDRESS_MAP_ROOT = "Resources/Map/level";
const string ADDRESS_LEADERBOARD = "Resources/Image/leaderboard/leaderboard.png";
const string ADDRESS_LOGIN_BOARD = "Resources/Image/board/boardLogin.png";
const string ADDRESS_USERNAME_BUTTON = "Resources/Image/button/login_button_username.png";
const string ADDRESS_PASSWORD_BUTTON = "Resources/Image/button/login_button_password.png";
const string ADDRESS_LOGIN_LOGIN_BUTTON = "Resources/Image/button/login_button_login.png";
const string ADDRESS_LOGIN_LOGIN_BUTTON_CLICK = "Resources/Image/button/login_button_login_click.png";
const string ADDRESS_ITERATOR_MOUSE = "Resources/Image/button/iteratorMouse.png";
const string ADDRESS_REGISTER_BOARD = "Resources/Image/board/boardRegister.png";
const string ADDRESS_REGISTER_USERNAME_BUTTON = "Resources/Image/button/register_button_username.png";
const string ADDRESS_REGISTER_PASSWORD_BUTTON = "Resources/Image/button/register_button_password.png";
const string ADDRESS_REGISTER_REGISTER_BUTTON = "Resources/Image/button/register_button_register.png";
const string ADDRESS_REGISTER_REGISTER_BUTTON_CLICK = "Resources/Image/button/register_button_register_click.png";
const string ADDRESS_SETTINGS_BOARD = "Resources/Image/settingsBoard/settingsBoard.png";
const string ADDRESS_SETTINGS_BOARD_SOUND_ON_BUTTON = "Resources/Image/settingsBoard/settingsBoard_OnButton.png";
const string ADDRESS_SETTINGS_BOARD_SOUND_ON_BUTTON_CLICK = "Resources/Image/settingsBoard/settingsBoard_OnButton_Click.png";
const string ADDRESS_SETTINGS_BOARD_SOUND_OFF_BUTTON = "Resources/Image/settingsBoard/settingsBoard_OffButton.png";
const string ADDRESS_SETTINGS_BOARD_SOUND_OFF_BUTTON_CLICK = "Resources/Image/settingsBoard/settingsBoard_OffButton_Click.png";
const string ADDRESS_SETTINGS_BOARD_SAVE_BUTTON = "Resources/Image/settingsBoard/settingsBoard_SaveButton.png";
const string ADDRESS_SETTINGS_BOARD_SAVE_BUTTON_CLICK = "Resources/Image/settingsBoard/settingsBoard_SaveButton_Click.png";
const string ADDRESS_SETTINGS_BOARD_RESTORE_BUTTON = "Resources/Image/settingsBoard/settingsBoard_RestoreButton.png";
const string ADDRESS_SETTINGS_BOARD_RESTORE_BUTTON_CLICK = "Resources/Image/settingsBoard/settingsBoard_RestoreButton_click.png";
const string ADDRESS_SETTINGS_BOARD_BACK_BUTTON = "Resources/Image/settingsBoard/settingsBoard_BackButton.png";
const string ADDRESS_SETTINGS_BOARD_BACK_BUTTON_CLICK = "Resources/Image/settingsBoard/settingsBoard_BackButton_click.png";
const string ADDRESS_SETTINGS_BOARD_EXIT_BUTTON = "Resources/Image/settingsBoard/settingsBoard_exitButton.png";
const string ADDRESS_SETTINGS_BOARD_EXIT_BUTTON_CLICK = "Resources/Image/settingsBoard/settingsBoard_exitButton_Click.png";
const string ADDRESS_HOWTOPLAY = "Resources/Image/HowToPlay/HowToPlay.png";
const string ADDRESS_SETTINGS_BUTTON = "Resources/Image/button/settings_button.png";
const string ADDRESS_SETTINGS_BUTTON_CLICK = "Resources/Image/button/settings_button_click.png";

const string ADDRESS_GBAR_LIFE = "Resources/Image/life/gbar_Life.png";
const string ADDRESS_GBAR_RING = "Resources/Image/rings/gbar_Ring.png";
const string ADDRESS_GAMEOVER = "Resources/Image/gameover/gameover.png";

const string ADDRESS_FONT_GAME = "Resources/Font/no_continue.ttf";
const string ADDRESS_BALL = "Resources/Image/ball/ball.png";
const string ADDRESS_BALL_POP = "Resources/Image/ball/ball_pop.png";
const string ADDRESS_DYN_THORN = "Resources/Image/threats/dyn_thorn.png";
const string ADDRESS_THORN = "Resources/Image/threats/thorn.png";
const string ADDRESS_RING_HORIZONTAL = "Resources/Image/rings/RING_HORIZONTAL.png";
const string ADDRESS_RING_HORIZONTAL_CATCHED = "Resources/Image/rings/RING_HORIZONTAL_catched.png";
const string ADDRESS_RING_VERTICAL = "Resources/Image/rings/RING_VERTICAL.png";
const string ADDRESS_RING_VERTICAL_CATCHED = "Resources/Image/rings/RING_VERTICAL_catched.png";
const string ADDRESS_CHECKPOINT = "Resources/Image/checkpoint/checkpoint.png";
const string ADDRESS_CHECKPOINT_CATCHED = "Resources/Image/checkpoint/checkpoint_catched.png";
const string ADDRESS_CHECKPOINT_CLEAR = "Resources/Image/checkpoint/checkpoint_clear.png";
const string ADDRESS_LIFE = "Resources/Image/life/life.png";
const string ADDRESS_LIFE_CLEAR = "Resources/Image/life/life_clear.png";
const string ADDRESS_ENDPOINT = "Resources/Image/ENDPOINT/ENDPOINT.png";
const string ADDRESS_ENDPOINT_OPENED = "Resources/Image/ENDPOINT/ENDPOINT_opened.png";

const string ADDRESS_SOUND_BALLPOP = "Resources/Sound/Ballpop.wav";
const string ADDRESS_SOUND_MUSICTYPE1 = "Resources/Sound/musicType1.wav";
const string ADDRESS_SOUND_MUSICTYPE2 = "Resources/Sound/musicType2.wav";

const string USERNAME_DEFAULT = "username";
const string PASSWORD_DEFAULT = "password";

const string NOTIFICATION_CONGRATULATIONS_COMPLETED_ALL_LEVEL = "Congratulations! You've completed all the levels";
const string NOTIFICATION_LOGIN_SUCCESS = "Login successfully";
const string NOTIFICATION_LOGIN_FAIL = "Wrong account or password";
const string TITLE_REGISTER_SUCCESS = "Register successfully";
const string TITLE_REGISTER_FAIL = "Failed to Register";


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