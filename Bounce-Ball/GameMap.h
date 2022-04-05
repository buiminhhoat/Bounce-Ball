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

	void LoadMap(const char* NameFileMap);
	void LoadIMGBlock(SDL_Renderer* Screen);
	void DrawMap(SDL_Renderer* Screen);
	Map getMap() const { return game_map_; }
	void SetMap(Map& map_data) {
		game_map_ = map_data;
	}
	Map GetMap() {
		return game_map_;
	}
	void FixMap();
	int Get_start_x_player() { return game_map_.start_x_player_; };
	int Get_start_y_player() { return game_map_.start_y_player_; };
private:
	Map game_map_;
	Block type_block[MAX_TYPE_BLOCKS];
};
#endif game_map__H_
#pragma once
