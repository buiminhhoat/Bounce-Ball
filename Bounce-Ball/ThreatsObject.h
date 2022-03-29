#ifndef THREATS__OBJECT__H
#define THREATS__OBJECT__H

#include "CommonFunc.h"
#include "BaseObject.h"

#define THREAT_FRAME_NUM 1
#define THREAT_SPEED 1

class ThreatsObject : public BaseObject {
public:
	ThreatsObject();
	~ThreatsObject();

	enum TypeMove {
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
	};

	void Set_x_val(const float& xVal) { x_val_ = xVal; }
	void Set_y_val(const float& yVal) { y_val_ = yVal; }

	void Set_x_pos(const float& xPos) { x_pos_ = xPos; }
	void Set_y_pos(const float& yPos) { y_pos_ = yPos; }

	float Get_x_pos() const { return x_pos_; }
	float Get_y_pos() const { return y_pos_; }

	void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; }

	void SetClips();

	bool LoadImage(std::string path, SDL_Renderer* Screen);

	void ShowImage(SDL_Renderer* des);

	int Get_width_frame() const { return width_frame_; };
	int Get_height_frame() const { return height_frame_; };

	void DoPlayer(Map& gMap);
	void CheckToMap(Map& gMap);
	void InitThreats();
	void Set_type_move(const int& typeMove) { type_move_ = typeMove; };
	void SetAnimationPos(const int& pos_a, const int& pos_b) { 
		animation_a_ = pos_a; 
		animation_b_ = pos_b; 
	};
	void Set_input_up(const int& ipUp) { input_type_.up_ = ipUp; };
	void ImpMoveType(SDL_Renderer* Screen);
private:
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	int type_move_;
	int animation_a_;
	int animation_b_;
	Input input_type_;
};
#endif#pragma once
