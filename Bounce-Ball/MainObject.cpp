#include "MainObject.h"
#include "BaseObject.h"

#define debug1(a) cout << #a << " = " << a << ";"
#define debug1l(a) cout << #a << " = " << a << ";" << '\n'
#define debug2(a, b) cout << #a << " = " << a << "; " << #b << " = " << b << "; "
#define debug2l(a, b) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << '\n'
#define debug3(a, b, c) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; "
#define debug3l(a, b, c) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << '\n'
#define debug4(a, b, c, d) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << #d << " = " << d << "; "
#define debug4l(a, b, c, d) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << #d << " = " << d << "; " << '\n'

using namespace std;

MainObject::MainObject() {
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
	come_back_time = 0;
	id_checkpoint_ = -1;
}

MainObject::~MainObject() {
	CleanUp();
}

bool MainObject::LoadImage(std::string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImage(path, Screen);
	if (ret == true) {
		width_frame_ = Rect_.w / TILE_LAYER;
		height_frame_ = Rect_.h;
	}
	return ret;
}

void MainObject::Set_Clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < TILE_LAYER; ++i) {
			frame_clip[i].x = i * width_frame_;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame_;
			frame_clip[i].h = height_frame_;
		}
	}
}

void MainObject::ShowImage(SDL_Renderer* des) {
	if (input_type_.left_ == 1 || input_type_.right_ == 1) {
		++frame_;
	}
	else {
		frame_ = 0;
	}

	if (frame_ >= TILE_LAYER) {
		frame_ = 0;
	}

	if (come_back_time == 0) {
		Rect_.x = x_pos_ - map_x_;
		Rect_.y = y_pos_ - map_y_;

		//SDL_Rect* current_clip = &frame_clip[frame];

		SDL_Rect renderQuad = { Rect_.x, Rect_.y, width_frame_, height_frame_ };

		SDL_RenderCopy(des, Object_, &frame_clip[frame_], &renderQuad);
	}
}

void MainObject::InputAction(SDL_Event events, SDL_Renderer* Screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
			case SDLK_RIGHT: {
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
			}
			break;
			case SDLK_LEFT: {
				status_ = WALK_LEFT;
				input_type_.left_ = 1;
				input_type_.right_ = 0;
			}
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
			case SDLK_RIGHT: {
				input_type_.right_ = 0;
			}
			break;
			case SDLK_LEFT: {
				input_type_.left_ = 0;
			}
			break;
		}
	}

	if (events.key.keysym.sym == SDLK_SPACE) {
		input_type_.jump_ = 1;
	}
	//if (events.type == SDL_MOUSEBUTTONDOWN) {
	//	if (events.button.button == SDL_BUTTON_RIGHT) {
	//		input_type_.jump_ = 1;
	//	}
	//}
}

void MainObject::DoPlayer(Map &map_data) {
	if (come_back_time == 0) {
		x_val_ = 0;
		y_val_ += GRAVITY_SPEED;
		if (y_val_ >= MAX_FALL_SPEED) {
			y_val_ = MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1) {
			x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ == 1) {
			x_val_ += PLAYER_SPEED;
		}

		if (input_type_.jump_ == 1) {
			if (on_ground_ == true) {
				y_val_ = -PLAYER_JUMP;
			}
			on_ground_ = false;
			input_type_.jump_ = 0;
		}
		CheckPlayerVsMap(map_data);
		CenterEntityOnMap(map_data);
	}

	if (come_back_time > 0) {
		--come_back_time;
		if (come_back_time == 0) {
			on_ground_ = false;
			if (x_pos_ > 256) {
				x_pos_ -= 256; // 4 tiles
				//map_x_ -= 256;
			}
			else {
				x_pos_ = 0;
			}
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
		}
	}
}

void MainObject::CenterEntityOnMap(Map &map_data) {
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0) {
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) {
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y_ < 0) {
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_) {
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void MainObject::CheckPlayerVsMap(Map& map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) {
			if (map_data.block[y1][x2] != BLANK_TILE || map_data.block[y2][x2] != BLANK_TILE) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) {
			if (map_data.block[y1][x1] != BLANK_TILE || map_data.block[y2][x1] != BLANK_TILE) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}
	else {
		x_val_ = 0;
	}

	// Check vertical
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		float height_block1 = (x1 + 1) * TILE_SIZE - x_pos_;
		float height_block2 = height_frame_ - height_block1;
		int select_block = 0;
		if (select_block == 0 && map_data.block[y2][x1] != BLANK_TILE) {
			if (height_block1 >= (1 - EQUILIBRIUM_RATIO) * width_frame_)
				select_block = 1;
		}
		if (select_block == 0 && map_data.block[y2][x2] != BLANK_TILE) {
			if (height_block2 >= (1 - EQUILIBRIUM_RATIO) * width_frame_)
				select_block = 2;
		}
		if (select_block == 0) {
			if (height_block1 > height_block2)
				select_block = 1;
			else
				select_block = 2;
		}

		if (y_val_ > 0) {
			if (height_block1 == TILE_SIZE) {
				if (map_data.block[y2][x1] != BLANK_TILE) {
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= height_frame_;
					y_val_ = 0;
					on_ground_ = true;
				}
			}
			else if (height_block2 == TILE_SIZE) {
				if (map_data.block[y2][x2] != BLANK_TILE) {
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= height_frame_;
					y_val_ = 0;
					on_ground_ = true;
				}
			}
			else if (map_data.block[y2][x1] != BLANK_TILE) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_;
				y_val_ = 0;
				on_ground_ = true;
				if (height_block1 <= (1 - EQUILIBRIUM_RATIO) * width_frame_
					&& map_data.block[y2][x2] == BLANK_TILE)
					if (height_block1 <= FREE_ROLLING_SPEED)
						x_pos_ += height_block1;
					else
						x_pos_ += FREE_ROLLING_SPEED;
			}
			else if (map_data.block[y2][x2] != BLANK_TILE) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_;
				y_val_ = 0;
				on_ground_ = true;
				if (height_block2 <= (1 - EQUILIBRIUM_RATIO) * width_frame_
					&& map_data.block[y2][x1] == BLANK_TILE)
					if (height_block2 <= FREE_ROLLING_SPEED)
						x_pos_ -= height_block2;
					else
						x_pos_ -= FREE_ROLLING_SPEED;
			}
		}
		else if (y_val_ < 0) {
			if (height_block1 == TILE_SIZE) {
				if (map_data.block[y1][x1] != BLANK_TILE) {
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			}
			else if (height_block2 == TILE_SIZE) {
				if (map_data.block[y1][x2] != BLANK_TILE) {
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			}
			else if (map_data.block[y1][x1] != BLANK_TILE) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				if (height_block1 <= (1 - EQUILIBRIUM_RATIO) * width_frame_
					&& map_data.block[y1][x2] == BLANK_TILE)
					if (height_block1 <= FREE_ROLLING_SPEED)
						x_pos_ += height_block1;
					else
						x_pos_ += FREE_ROLLING_SPEED;
				y_val_ = 0;
			}
			else if (map_data.block[y1][x2] != BLANK_TILE) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				if (height_block2 <= (1 - EQUILIBRIUM_RATIO) * width_frame_
					&& map_data.block[y1][x1] == BLANK_TILE)
					if (height_block2 <= FREE_ROLLING_SPEED)
						x_pos_ -= height_block2;
					else
						x_pos_ -= FREE_ROLLING_SPEED;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_;
	}

	if (y_pos_ < 0) {
		y_pos_ = 0;
	}
	if (y_pos_ > map_data.max_y_) {
		//y_pos_ = 0;
		come_back_time = 10;
	}
}