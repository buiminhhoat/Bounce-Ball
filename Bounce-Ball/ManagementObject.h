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

	void LoadALLObject(MainObject& Player, GameMap& gamemap, SDL_Renderer* Screen);
	void checkIntersectALLObject(ScoreObject& Score, MainObject& Player, Map& map_data, SDL_Renderer* Screen);

	int Get_is_IntersectBallVsThreats() {return is_IntersectBallVsThreats_;}

	void Set_is_IntersectBallVsThreats(const int &val_is_IntersectBallVsObject) {
		is_IntersectBallVsThreats_ = val_is_IntersectBallVsObject;
	}

	int Get_is_IntersectBallVsRing() { return is_IntersectBallVsRing_; }

	void Set_is_IntersectBallVsRing(const int & is_IntersectBallVsRing) {
		is_IntersectBallVsRing_ = is_IntersectBallVsRing;
	}
private:
	std::vector <ThreatsObject*> threats_list;
	std::vector <RingsObject*> rings_list;
	std::vector <CheckpointObject*> checkpoints_list;

	int is_IntersectBallVsThreats_;
	int is_IntersectBallVsRing_;
};
#endif
#pragma once
