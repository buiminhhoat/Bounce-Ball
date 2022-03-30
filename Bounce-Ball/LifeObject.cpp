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
#include "TextObject.h"
#include "LifeObject.h"

#include "LevelGame.h"

#include "ManagementObject.h"

using namespace std;

LifeObject::LifeObject() {
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ = false;
	come_back_time_ = 0;
	frame_ = 0;
	animation_a_ = 0;
	animation_b_ = 0;
	is_catched_ = 0;
	ScoreLife_ = 0;
	is_Vertical_ = 0;
	Life_ = 0;
}

LifeObject::~LifeObject() {

}

bool LifeObject::LoadImage(std::string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImage(path, Screen);
	if (ret) {
		width_frame_ = Rect_.w / LIFE_FRAME_NUM;
		height_frame_ = Rect_.h;
	}
	return ret;
}

void LifeObject::SetClips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < LIFE_FRAME_NUM; ++i) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void LifeObject::ShowImage(SDL_Renderer* des) {
	if (come_back_time_ == 0) {
		Rect_.x = x_pos_ - map_x_;
		Rect_.y = y_pos_ - map_y_;
		++frame_;
		if (frame_ >= LIFE_FRAME_NUM) {
			frame_ = 0;
		}

		SDL_Rect rendQuad = { Rect_.x, Rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, Object_, &frame_clip_[frame_], &rendQuad);
	}
}