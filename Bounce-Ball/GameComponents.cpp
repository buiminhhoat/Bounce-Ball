#include "GameComponents.h"

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

RingsObject::RingsObject() {
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
	ScoreRing_ = 0;
	is_Vertical_ = 0;
}

RingsObject::~RingsObject() {

}

bool RingsObject::LoadImage(std::string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImage(path, Screen);
	if (ret) {
		width_frame_ = Rect_.w / RINGS_FRAME_NUM;
		height_frame_ = Rect_.h;
	}
	return ret;
}

void RingsObject::SetClips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < RINGS_FRAME_NUM; ++i) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void RingsObject::ShowImage(SDL_Renderer* des) {
	if (come_back_time_ == 0) {
		Rect_.x = x_pos_ - map_x_;
		Rect_.y = y_pos_ - map_y_;
		++frame_;
		if (frame_ >= RINGS_FRAME_NUM) {
			frame_ = 0;
		}

		SDL_Rect rendQuad = { Rect_.x, Rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, Object_, &frame_clip_[frame_], &rendQuad);
	}
}

ScoreObject::ScoreObject() {
	Score = 0;
}

ScoreObject::~ScoreObject() {

}

EndpointObject::EndpointObject() {
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
	is_opened_ = 0;
	ScoreEndpoint_ = 0;
}

EndpointObject::~EndpointObject() {

}

bool EndpointObject::LoadImage(std::string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImage(path, Screen);
	if (ret) {
		width_frame_ = Rect_.w / ENDPOINT_FRAME_NUM;
		height_frame_ = Rect_.h;
	}
	return ret;
}

void EndpointObject::SetClips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < ENDPOINT_FRAME_NUM; ++i) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void EndpointObject::ShowImage(SDL_Renderer* des) {
	if (come_back_time_ == 0) {
		Rect_.x = x_pos_ - map_x_;
		Rect_.y = y_pos_ - map_y_;
		++frame_;
		if (frame_ >= ENDPOINT_FRAME_NUM) {
			frame_ = 0;
		}

		SDL_Rect rendQuad = { Rect_.x, Rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, Object_, &frame_clip_[frame_], &rendQuad);
	}
}

ThreatsObject::ThreatsObject() {
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
	input_type_.left_ = 0;
	type_move_ = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject() {

}

bool ThreatsObject::LoadImage(std::string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImage(path, Screen);
	if (ret) {
		width_frame_ = Rect_.w / THREAT_FRAME_NUM;
		height_frame_ = Rect_.h;
	}
	return ret;
}

void ThreatsObject::SetClips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < THREAT_FRAME_NUM; ++i) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void ThreatsObject::ShowImage(SDL_Renderer* des) {
	if (come_back_time_ == 0) {
		Rect_.x = x_pos_ - map_x_;
		Rect_.y = y_pos_ - map_y_;
		++frame_;
		if (frame_ >= THREAT_FRAME_NUM) {
			frame_ = 0;
		}

		SDL_Rect rendQuad = { Rect_.x, Rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, Object_, &frame_clip_[frame_], &rendQuad);
	}
}

void ThreatsObject::InitThreats() {
	x_val_ = 0;
	y_val_ = 0;
	//if (y_pos_ > 256) {
	//	y_pos_ -= 256;
	//	animation_a_ -= 256;
	//	animation_b_ -= 256;
	//}
	//else {
	//	y_pos_ = 0;
	//}
	x_pos_ = 0;
	come_back_time_ = 0;
	input_type_.up_ = 1;
}

void ThreatsObject::DoPlayer(Map& gMap) {
	if (type_move_ == STATIC_THREAT) return;
	x_val_ = 0;
	y_val_ += THREAT_GRAVITY_SPEED;
	if (y_val_ >= THREAT_MAX_FALL_SPEED) {
		y_val_ = THREAT_MAX_FALL_SPEED;
	}

	if (input_type_.up_ == 1) {
		y_val_ -= THREAT_SPEED;
	}
	else if (input_type_.down_ == 1) {
		y_val_ += THREAT_SPEED;
	}
	CheckToMap(gMap);
}

void ThreatsObject::CheckToMap(Map& gMap) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	// Check horizontal
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (x_val_ > 0) {
			if (gMap.block[y1][x2] != BLANK_TILES || gMap.block[y2][x2] != BLANK_TILES) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_;
				x_val_ = 0;
			}
		}
		else {
			if (gMap.block[y1][x1] != BLANK_TILES || gMap.block[y2][x1] != BLANK_TILES) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	// Check vertical
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			if (gMap.block[y2][x1] != BLANK_TILES || gMap.block[y2][x2] != BLANK_TILES) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_);
				y_val_ = 0;
				on_ground_ = true;
				if (type_move_ == TypeMove::MOVE_IN_SPACE_THREAT) {
					input_type_.down_ = 0;
					input_type_.up_ = 1;
				}
			}
		}
		else if (y_val_ < 0) {
			if (gMap.block[y1][x1] != BLANK_TILES || gMap.block[y1][x2] != BLANK_TILES) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
				if (type_move_ == TypeMove::MOVE_IN_SPACE_THREAT) {
					input_type_.down_ = 1;
					input_type_.up_ = 0;
				}
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > gMap.max_x_) {
		x_pos_ = gMap.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ < 0) {
		y_pos_ = THREAT_SPEED;
		input_type_.up_ = 0;
		input_type_.down_ = 1;
	}
	if (y_pos_ > gMap.max_y_) {
		come_back_time_ = 10;
	}
}

void ThreatsObject::ImpMoveType(SDL_Renderer* Screen) {
	if (type_move_ == STATIC_THREAT) {
		;
	}
	else {
		if (y_pos_ > animation_b_) {
			input_type_.up_ = 1;
			input_type_.down_ = 0;
			LoadImage("img//threats//dyn_thorn.png", Screen);
		}
		else if (y_pos_ < animation_a_) {
			input_type_.up_ = 0;
			input_type_.down_ = 1;
			LoadImage("img//threats//dyn_thorn.png", Screen);
		}
	}
}

CheckpointObject::CheckpointObject() {
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
	ScoreRing_ = 0;
	is_Vertical_ = 0;
}

CheckpointObject::~CheckpointObject() {

}

bool CheckpointObject::LoadImage(std::string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImage(path, Screen);
	if (ret) {
		width_frame_ = Rect_.w / CHECKPOINT_FRAME_NUM;
		height_frame_ = Rect_.h;
	}
	return ret;
}

void CheckpointObject::SetClips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < CHECKPOINT_FRAME_NUM; ++i) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void CheckpointObject::ShowImage(SDL_Renderer* des) {
	if (come_back_time_ == 0) {
		Rect_.x = x_pos_ - map_x_;
		Rect_.y = y_pos_ - map_y_;
		++frame_;
		if (frame_ >= CHECKPOINT_FRAME_NUM) {
			frame_ = 0;
		}

		SDL_Rect rendQuad = { Rect_.x, Rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, Object_, &frame_clip_[frame_], &rendQuad);
	}
}

TextObject::TextObject() {
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;
	texture_ = NULL;
}

TextObject::~TextObject() {

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* Screen) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text_val_.c_str(), text_color_);
	if (text_surface != NULL) {
		texture_ = SDL_CreateTextureFromSurface(Screen, text_surface);
		width_ = text_surface->w;
		height_ = text_surface->h;
		SDL_FreeSurface(text_surface);
	}
	return (text_surface != NULL);
}

void TextObject::CleanUp() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
	text_color_.r = red;
	text_color_.g = green;
	text_color_.b = blue;
}

void TextObject::SetColor(int type) {
	if (type == RED_COLOR) {
		SDL_Color color = { 255, 0, 0 };
		text_color_ = color;
	}
	if (type == ORANGE_COLOR) {
		SDL_Color color = { 255, 165, 0 };
		text_color_ = color;
	}
	if (type == YELLOW_COLOR) {
		SDL_Color color = { 255, 255, 0 };
		text_color_ = color;
	}
	if (type == GREEN_COLOR) {
		SDL_Color color = { 0, 255, 0 };
		text_color_ = color;
	}
	if (type == BLUE_COLOR) {
		SDL_Color color = { 0, 0, 255 };
		text_color_ = color;
	}
	if (type == INDIGO_COLOR) {
		SDL_Color color = { 75, 0, 130 };
		text_color_ = color;
	}
	if (type == PURPLE_COLOR) {
		SDL_Color color = { 128, 0, 128 };
		text_color_ = color;
	}
	if (type == WHITE_COLOR) {
		SDL_Color color = { 255, 255, 255 };
		text_color_ = color;
	}
	if (type == BLACK_COLOR) {
		SDL_Color color = { 0, 0, 0 };
		text_color_ = color;
	}
}

void TextObject::ShowText(SDL_Renderer* Screen,
	int x_pos_text, int y_pos_text,
	SDL_Rect* clip /* = NULL */,
	double angle /* = 0.0 */,
	SDL_Point* center /* = NULL */,
	SDL_RendererFlip flip /* = SDL_FLIP_NONE */) {
	SDL_Rect renderQuad = { x_pos_text, y_pos_text, width_, height_ };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(Screen, texture_, clip, &renderQuad, angle, center, flip);
	CleanUp();
}

bool ButtonObject::LoadImage(std::string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImage(path, Screen);
	if (ret) {
		width_frame_ = Rect_.w / BUTTON_FRAME_NUM;
		height_frame_ = Rect_.h;
	}
	return ret;
}

void ButtonObject::SetClips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < BUTTON_FRAME_NUM; ++i) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void ButtonObject::ShowImage(SDL_Renderer* des) {
	if (come_back_time_ == 0) {
		Rect_.x = x_pos_ - map_x_;
		Rect_.y = y_pos_ - map_y_;
		++frame_;
		if (frame_ >= CHECKPOINT_FRAME_NUM) {
			frame_ = 0;
		}

		SDL_Rect rendQuad = { Rect_.x, Rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, Object_, &frame_clip_[frame_], &rendQuad);
	}
}

InfoPlayer::InfoPlayer() {
	namePlayer = "";
	score = 0;
	life = ORIGINAL_LIFE;
}

InfoPlayer::~InfoPlayer() {

}