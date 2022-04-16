#ifndef __BOUNCEBALL__
#define __BOUNCEBALL__

#include <vector>
#include <string>
#include <fstream>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"
#include "GameComponents.h"
#include "LevelGame.h"
#include "ManagementObject.h"
#include "Database.h"

class BounceBall {
public:
	enum selectInput {
		ACCOUNT = 1,
		PASSWORD = 2,
	};

	enum showDisplay {
		MENU = 0,
		PLAY = 1,
		LEADERBOARD = 2,
		LOGIN = 3,
		HIDE_LOGIN = 4, 
		RE_MENU = 5,
	};

	enum typeLevel {
		GAME_OVER = 0,
		NEXT_LEVEL = 1,
		QUIT_GAME = 2,
		ERROR_GAME = 3,
	};

	BounceBall();
	~BounceBall();
	int startGame();
	bool initSDL();
	void cleanUp();
	void displayLogo();
	void displayPlay();
	void displayLeaderboard();
	bool checkInfoLogin(string username, string password, InfoPlayer* infoPlayer);
	void displayLogin();
	void setDisplay(int display) { this->display = display; }
private:
	int display = 0;
	Database databaseGame;
};
#endif
#pragma once
