#ifndef MAIN__OBJECT_H_
#define MAIN__OBJECT_H_

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP 20
#define EQUILIBRIUM_RATIO 0.70
#define FREE_ROLLING_SPEED 5

class MainObject : public BaseObject {
public:
	MainObject();
	~MainObject();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};

	bool LoadImage(std::string path, SDL_Renderer* Screen);
	void ShowImage(SDL_Renderer* des);
	void InputAction(SDL_Event events, SDL_Renderer* Screen);
	void Set_Clips();
	void DoPlayer(Map& map_data);
	void CheckPlayerVsMap(Map& mapdata);
	void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x;map_y_ = map_y;}
	void CenterEntityOnMap(Map& map_data);
	int come_back_time;
	float Get_x_pos() { return x_pos_; };
	float Get_y_pos() { return y_pos_; };


	float Get_width_frame() { return width_frame_; };
	float Get_height_frame() { return height_frame_; };
	void Set_pos(const float &pos_x, const float &pos_y) {
		x_pos_ = pos_x;
		y_pos_ = pos_y;
	}

	void Set_pos_checkpoint(const float &pos_x, const float &pos_y) {
		x_checkpoint_ = pos_x;
		y_checkpoint_ = pos_y;
	}

	float Get_x_pos_checkpoint() { return x_checkpoint_; };
	float Get_y_pos_checkpoint() { return y_checkpoint_; };

	int Get_id_checkpoint() { return id_checkpoint_; };
	void Set_id_checkpoint(const int& id_checkpoint) { id_checkpoint_ = id_checkpoint; };
private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	float x_checkpoint_;
	float y_checkpoint_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip[8];
	Input input_type_;
	int frame_;
	int status_;
	int on_ground_;

	int map_x_;
	int map_y_;

	int id_checkpoint_;
};
#endif
#pragma once
