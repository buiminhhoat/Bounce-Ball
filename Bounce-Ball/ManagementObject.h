#ifndef __MANAGEMENTOBJECT__
#define __MANAGEMENTOBJECT__

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

using namespace std;

class ManagementObject {
public:
	ManagementObject();
	~ManagementObject();
	void LoadThreatsObject(SDL_Renderer* Screen);
	void checkIntersectThreatsObject(SDL_Renderer* Screen);
	
	void LoadRingsObject(SDL_Renderer* Screen);
	void checkIntersectRingsObject(SDL_Renderer* Screen);
	
	void LoadCheckpointObject(SDL_Renderer* Screen);
	void checkIntersectCheckpointObject(SDL_Renderer* Screen);

	void LoadLifeObject(SDL_Renderer* Screen);
	void checkIntersectLifeObject(SDL_Renderer* Screen);

	void LoadEndpointObject(SDL_Renderer* Screen);
	void OpenAllEndpointObject(SDL_Renderer* Screen);
	void checkIntersectEndpointObject(SDL_Renderer* Screen);

	void LoadALLObject(InfoPlayer* infoPlayer, SDL_Renderer* Screen);
	void checkIntersectALLObject(SDL_Renderer* Screen);

	int Get_is_IntersectBallVsThreats() {return is_IntersectBallVsThreats_;}

	void Set_is_IntersectBallVsThreats(const int &val_is_IntersectBallVsObject) {
		is_IntersectBallVsThreats_ = val_is_IntersectBallVsObject;
	}

	int Get_is_IntersectBallVsRing() { return is_IntersectBallVsRing_; }

	void Set_is_IntersectBallVsRing(const int & is_IntersectBallVsRing) {
		is_IntersectBallVsRing_ = is_IntersectBallVsRing;
	}

	int Get_is_IntersectBallVsEndpoint_() {
		return is_IntersectBallVsEndpoint_;
	}

	void Set_is_IntersectBallVsEndpoint_(int is_IntersectBallVsEndpoint_) {
		this->is_IntersectBallVsEndpoint_ = 0;
	}

	void Set_rem_Rings(const int& rem_Rings) { rem_Rings_ = rem_Rings; }
	int Get_rem_Rings() { return rem_Rings_; };

	void setAllObject(GameMap *gamemap,	MainObject *Player, ScoreObject *Score, 
						LifeObject *Life, InfoPlayer *infoPlayer) {
		gamemap_ = gamemap;
		Player_ = Player;
		Score_ = Score;
		Life_ = Life;
		map_data_ = gamemap->getMap();
		this->infoPlayer_ = infoPlayer;
	}
private:
	std::vector <ThreatsObject*> threats_list;
	std::vector <RingsObject*> rings_list;
	std::vector <CheckpointObject*> checkpoints_list;
	std::vector <LifeObject*> lifes_list;
	std::vector <EndpointObject*> endpoints_list;

	int is_IntersectBallVsThreats_;
	int is_IntersectBallVsRing_;
	int is_IntersectBallVsEndpoint_;
	int rem_Rings_;

	GameMap *gamemap_;
	MainObject *Player_;
	Map map_data_;
	ScoreObject *Score_;
	LifeObject *Life_;
	InfoPlayer* infoPlayer_;
};
#endif