#ifndef __Management__
#define __Management__

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

using namespace std;

class Management {
public:
	Management();
	~Management();
	void loadThreatsObject(SDL_Renderer* screen);
	void checkIntersectThreatsObject(SDL_Renderer* screen);
	
	void loadRingsObject(SDL_Renderer* screen);
	void checkIntersectRingsObject(SDL_Renderer* screen);
	
	void loadCheckpointObject(SDL_Renderer* screen);
	void checkIntersectCheckpointObject(SDL_Renderer* screen);

	void loadLifeObject(SDL_Renderer* screen);
	void checkIntersectLifeObject(SDL_Renderer* screen);

	void loadEndpointObject(SDL_Renderer* screen);
	void openAllEndpointObject(SDL_Renderer* screen);
	void checkIntersectEndpointObject(SDL_Renderer* screen);

	void loadAllObject(InfoPlayer* infoPlayer, SDL_Renderer* screen);
	void checkIntersectAllObject(SDL_Renderer* screen);

	bool getIsIntersectBallVsThreats() {return this->isIntersectBallVsThreats;}

	void setIsIntersectBallVsThreats(const bool &valIsIntersectBallVsObject) {
		this->isIntersectBallVsThreats = valIsIntersectBallVsObject;
	}

	bool getIsIntersectBallVsRing() { return this->isIntersectBallVsRing; }

	void setIsIntersectBallVsRing(const bool & isIntersectBallVsRing) {
		this->isIntersectBallVsRing = isIntersectBallVsRing;
	}

	bool getIsIntersectBallVsEndpoint() {
		return this->isIntersectBallVsEndpoint;
	}

	void setIsIntersectBallVsEndpoint(bool isIntersectBallVsEndpoint) {
		this->isIntersectBallVsEndpoint = isIntersectBallVsEndpoint;
	}

	void setRemRings(const int& remRings) { this->remRings = remRings; }
	int getRemRings() { return this->remRings; };

	void setAllObject(GameMap *gamemap,	MainObject *player, ScoreObject *score, 
						LifeObject *life, InfoPlayer *infoPlayer) {
		this->gameMap = gamemap;
		this->player = player;
		this->score = score;
		this->life = life;
		this->mapData = gamemap->getMap();
		this->infoPlayer = infoPlayer;
	}
private:
	std::vector <ThreatsObject*> threatsList;
	std::vector <RingsObject*> ringsList;
	std::vector <CheckpointObject*> checkpointsList;
	std::vector <LifeObject*> lifesList;
	std::vector <EndpointObject*> endpointsList;

	bool isIntersectBallVsThreats;
	bool isIntersectBallVsRing;
	bool isIntersectBallVsEndpoint;
	int remRings;

	GameMap *gameMap;
	MainObject *player;
	Map *mapData;
	ScoreObject *score;
	LifeObject *life;
	InfoPlayer* infoPlayer;

	Mix_Chunk* ballPop;
	Mix_Chunk* intersectObject1;
	Mix_Chunk* intersectObject2;
};
#endif