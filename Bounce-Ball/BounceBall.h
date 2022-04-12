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

class BounceBall {
public:
	enum selectInput {
		ACCOUNT = 1,
		PASSWORD = 2,
	};
	BounceBall();
	~BounceBall();
	int startGame();
	bool initSDL();
	void cleanUp();
	void displayLogo();
	void displayMenu();  
	void displayPlay();
	void displayLeaderboard();
	bool checkInfoLogin(string username, string password);
	void displayLogin();
	void setDisplay(int display) { this->display = display; }
private:
	int display = 0;
};
#endif
#pragma once
