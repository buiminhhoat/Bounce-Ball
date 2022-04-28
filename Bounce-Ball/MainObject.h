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
public:
	MainObject();
	~MainObject();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};

	bool loadImage(std::string path, SDL_Renderer* screen);
	void showImage(SDL_Renderer* des);
	void inputAction(SDL_Event events, SDL_Renderer* screen);
	void setClips();
	void doPlayer(Map* mapData);
	void checkPlayerVsMap(Map* mapdata);
	void setMapXY(const int &map_x, const int &map_y) {this->mapX = map_x;this->mapY = map_y;}
	void centerEntityOnMap(Map* mapData);
	float getXPos() { return this->xPos; };
	float getYPos() { return this->yPos; };


	float getWidthFrame() { return this->widthFrame; };
	float getHeightFrame() { return this->heightFrame; };
	void setPos(const float & xPos, const float &yPos) {
		this->xPos = xPos;
		this->yPos = yPos;
	}

	void setPosCheckpoint(const float &xPosCheckpoint, const float &yPosCheckpoint) {
		this->xPosCheckpoint = xPosCheckpoint;
		this->yPosCheckpoint = yPosCheckpoint;
	}

	float getXPosCheckpoint() { return this->xPosCheckpoint; };
	float getYPosCheckpoint() { return this->yPosCheckpoint; };

	int getIdCheckpoint() { return this->idCheckpoint; };
	void setIdCheckpoint(const int& idCheckpoint) { this->idCheckpoint = idCheckpoint; };
private:
	float xVal;
	float yVal;

	float xPos;
	float yPos;

	float xPosCheckpoint;
	float yPosCheckpoint;

	float widthFrame;
	float heightFrame;

	SDL_Rect frameClip[8];
	Input inputType;
	int frame;
	int status;
	int onGround;

	int mapX;
	int mapY;

	int idCheckpoint;
};
#endif
#pragma once
