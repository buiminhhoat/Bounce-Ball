#ifndef __MAINOBJECT__
#define __MAINOBJECT__

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP 20
#define EQUILIBRIUM_RATIO 0.70
#define FREE_ROLLING_SPEED 5
#define DRAW_BACK 4 * 64

class MainObject : public BaseObject {
#define MAIN_FRAME_NUM 8
public:
	MainObject();
	~MainObject();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};

	void inputAction(SDL_Event events, SDL_Renderer* screen);
	void doPlayer(Map* mapData);
	void checkPlayerVsMap(Map* mapdata);
	void centerEntityOnMap(Map* mapData);

	void setPosCheckpoint(const float &xPosCheckpoint, const float &yPosCheckpoint) {
		this->xPosCheckpoint = xPosCheckpoint;
		this->yPosCheckpoint = yPosCheckpoint;
	}

	float getXPosCheckpoint() { return this->xPosCheckpoint; };
	float getYPosCheckpoint() { return this->yPosCheckpoint; };

	int getIdCheckpoint() { return this->idCheckpoint; };
	void setIdCheckpoint(const int& idCheckpoint) { this->idCheckpoint = idCheckpoint; };
private:
	float xPosCheckpoint;
	float yPosCheckpoint;

	Input inputType;
	int status;
	int onGround;
	int idCheckpoint;
};
#endif
#pragma once
