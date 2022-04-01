#ifndef MANAGEMENT__OBJECT__H_
#define MANAGEMENT__OBJECT__H_

#include <vector>
#include <string>
#include <fstream>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"

#include "ThreatsObject.h"
#include "RingsObject.h"
#include "ScoreObject.h"
#include "CheckpointObject.h"
#include "LifeObject.h"
#include "EndpointObject.h"

#include "LevelGame.h"

#include "ManagementObject.h"

using namespace std;

class ManagementObject {
public:
	ManagementObject();
	~ManagementObject();
	void LoadThreatsObject(GameMap &gamemap, SDL_Renderer* Screen);
	void checkIntersectThreatsObject(MainObject &Player, Map &map_data, SDL_Renderer* Screen);
	
	void LoadRingsObject(GameMap& gamemap, SDL_Renderer* Screen);
	void checkIntersectRingsObject(ScoreObject& Score, MainObject &Player, Map& map_data, SDL_Renderer* Screen);
	
	void LoadCheckpointObject(MainObject& Player, GameMap& gamemap, SDL_Renderer* Screen);
	void checkIntersectCheckpointObject(ScoreObject& Score, MainObject& Player, Map& map_data, SDL_Renderer* Screen);

	void LoadLifeObject(MainObject& Player, GameMap& gamemap, SDL_Renderer* Screen);
	void checkIntersectLifeObject(LifeObject& Life, ScoreObject& Score, MainObject& Player, Map& map_data, SDL_Renderer* Screen);

	void LoadEndpointObject(MainObject& Player, GameMap& gamemap, SDL_Renderer* Screen);
	void OpenAllEndpointObject(SDL_Renderer* Screen);
	void checkIntersectEndpointObject(ScoreObject& Score, MainObject& Player, Map& map_data, SDL_Renderer* Screen);

	void LoadALLObject(MainObject& Player, GameMap& gamemap, SDL_Renderer* Screen);
	void checkIntersectALLObject(LifeObject& Life, ScoreObject& Score, MainObject& Player, Map& map_data, SDL_Renderer* Screen);

	int Get_is_IntersectBallVsThreats() {return is_IntersectBallVsThreats_;}

	void Set_is_IntersectBallVsThreats(const int &val_is_IntersectBallVsObject) {
		is_IntersectBallVsThreats_ = val_is_IntersectBallVsObject;
	}

	int Get_is_IntersectBallVsRing() { return is_IntersectBallVsRing_; }

	void Set_is_IntersectBallVsRing(const int & is_IntersectBallVsRing) {
		is_IntersectBallVsRing_ = is_IntersectBallVsRing;
	}

	void Set_rem_Rings(const int& rem_Rings) { rem_Rings_ = rem_Rings; }
	int Get_rem_Rings() { return rem_Rings_; };
private:
	std::vector <ThreatsObject*> threats_list;
	std::vector <RingsObject*> rings_list;
	std::vector <CheckpointObject*> checkpoints_list;
	std::vector <LifeObject*> lifes_list;
	std::vector <EndpointObject*> endpoints_list;

	int is_IntersectBallVsThreats_;
	int is_IntersectBallVsRing_;
	int rem_Rings_;
};
#endif
#pragma once
