#ifndef __GAMEMAP__
#define __GAMEMAP__

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TYPE_BLOCKS 10

class Block : public BaseObject {
public:
	Block() { ; }
	~Block() { ; }
};

class GameMap {
public:
	GameMap() { ; }
	~GameMap() { ; }

	void loadMap(const char* nameFileMap);
	void loadIMGBlock(SDL_Renderer* screen);
	void drawMap(SDL_Renderer* screen);
	Map getMap() const { return gameMap; }
	void setMap(Map& gameMap) {
		this->gameMap = gameMap;
	}
	Map getMap() {
		return this->gameMap;
	}
	void fixMap();
	int getStartXPlayer() { return gameMap.startXPlayer; };
	int getStartYPlayer() { return gameMap.startYPlayer; };
private:
	Map gameMap;
	Block type_block[MAX_TYPE_BLOCKS];
};
#endif __GAMEMAP__
#pragma once
