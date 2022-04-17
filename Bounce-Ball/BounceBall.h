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

	enum typeDisplay {
		MENU = 0,
		PLAY = 1,
		LEADERBOARD = 2,
		LOGIN = 3,
		LOGOUT = 4,
		HOW_TO_PLAY = 5,
		SETTINGS = 6,
		RE_MENU = 7,
		REGISTER = 8,
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
	void displayLogout();
	void displayRegister();
	bool notificationStatusRegister(string usernameText, string passwordText);
private:
	int display = typeDisplay::MENU;
	Database databaseGame;
};
#endif
#pragma once
