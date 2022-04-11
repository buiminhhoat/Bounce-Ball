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
	BounceBall();
	~BounceBall();
	int startGame();
	bool initSDL();
	void CleanUp();
	void displayLogo();
	void displayMenu();
	void displayPlay();
	void displayLeaderboard();
	void displayLogin();
	void setDisplay(int display) {
		this->display = display;
	}
private:
	int display = 0;
};
#endif
#pragma once
