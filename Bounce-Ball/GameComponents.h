#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

#include "BaseObject.h"

using namespace std;

class LifeObject : public BaseObject {
	#define ORIGINAL_LIFE 10000
	#define LIFE_FRAME_NUM 1
	#define SCORE_LIFE 50
public:
	LifeObject();
	~LifeObject();

	void IncreaseLife(const int& valIncrease) {
		Life_ += valIncrease;
	};

	int GetLife() { return Life_; };

	void SetLife(const int& Life) {
		Life_ = Life;
	}

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

	void Set_type_move(const int& typeMove) { type_move_ = typeMove; };
	void SetAnimationPos(const int& pos_a, const int& pos_b) {
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	};

	int Get_is_catched() { return is_catched_; };
	void Set_is_catched(const int& is_catched) { is_catched_ = is_catched; };

	int Get_ScoreLife() { return ScoreLife_; };
	void Set_ScoreLife(const int& ScoreLife) { ScoreLife_ = ScoreLife; };

	int Get_is_Vertical() { return is_Vertical_; };
	void Set_is_Vertical(const int& is_Vertical) { is_Vertical_ = is_Vertical; };
private:
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[LIFE_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	int type_move_;
	int animation_a_;
	int animation_b_;
	int is_catched_;
	int ScoreLife_;
	int is_Vertical_;
	int Life_;
};

class RingsObject : public BaseObject {
#define RINGS_FRAME_NUM 1
#define SCORE_RING_HORIZONTAL 50
#define SCORE_RING_VERTICAL 100 
public:
	RingsObject();
	~RingsObject();

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

	void Set_type_move(const int& typeMove) { type_move_ = typeMove; };
	void SetAnimationPos(const int& pos_a, const int& pos_b) {
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	};

	int Get_is_catched() { return is_catched_; };
	void Set_is_catched(const int& is_catched) { is_catched_ = is_catched; };

	int Get_ScoreRing() { return ScoreRing_; };
	void Set_ScoreRing(const int& ScoreRing) { ScoreRing_ = ScoreRing; };

	int Get_is_Vertical() { return is_Vertical_; };
	void Set_is_Vertical(const int& is_Vertical) { is_Vertical_ = is_Vertical; };
private:
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[RINGS_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	int type_move_;
	int animation_a_;
	int animation_b_;
	int is_catched_;
	int ScoreRing_;
	int is_Vertical_;
};

class ScoreObject : public BaseObject {
public:
	ScoreObject();
	~ScoreObject();
	void IncreaseScore(const int& valIncrease) {
		Score += valIncrease;
	};
	int GetScore() { return Score; };
	void setScore(int Score) { this->Score = Score; }
private:
	int Score;
};

class EndpointObject : public BaseObject {
#define ENDPOINT_FRAME_NUM 1
#define SCORE_ENDPOINT 50
public:
	EndpointObject();
	~EndpointObject();

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

	void Set_type_move(const int& typeMove) { type_move_ = typeMove; };
	void SetAnimationPos(const int& pos_a, const int& pos_b) {
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	};

	int Get_is_opened() { return is_opened_; };
	void Set_is_opened(const int& is_opened) { is_opened_ = is_opened; };

	int Get_ScoreEndpoint() { return ScoreEndpoint_; };
	void Set_ScoreEndpoint(const int& ScoreEndpoint) { ScoreEndpoint_ = ScoreEndpoint; };
	
private:
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[ENDPOINT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	int type_move_;
	int animation_a_;
	int animation_b_;
	int is_opened_;
	int ScoreEndpoint_;
};

class ThreatsObject : public BaseObject {
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_FRAME_NUM 1
#define THREAT_SPEED 1
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

class CheckpointObject : public BaseObject {
#define CHECKPOINT_FRAME_NUM 1
#define SCORE_CHECKPOINT 25
public:
	CheckpointObject();
	~CheckpointObject();

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

	void Set_type_move(const int& typeMove) { type_move_ = typeMove; };
	void SetAnimationPos(const int& pos_a, const int& pos_b) {
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	};

	int Get_is_catched() { return is_catched_; };
	void Set_is_catched(const int& is_catched) { is_catched_ = is_catched; };

	int Get_ScoreRing() { return ScoreRing_; };
	void Set_ScoreRing(const int& ScoreRing) { ScoreRing_ = ScoreRing; };

	int Get_is_Vertical() { return is_Vertical_; };
	void Set_is_Vertical(const int& is_Vertical) { is_Vertical_ = is_Vertical; };
private:
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[CHECKPOINT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	int type_move_;
	int animation_a_;
	int animation_b_;
	int is_catched_;
	int ScoreRing_;
	int is_Vertical_;
};

class TextObject {
public:
	TextObject();
	~TextObject();

	enum {
		RED_COLOR,
		ORANGE_COLOR,
		YELLOW_COLOR,
		GREEN_COLOR,
		BLUE_COLOR,
		INDIGO_COLOR,
		PURPLE_COLOR,
		WHITE_COLOR,
		BLACK_COLOR,
	};

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* Screen);
	void CleanUp();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	void ShowText(SDL_Renderer* Screen,
		int x_pos_text, int y_pos_text,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth() { return width_; };
	int GetHeight() { return height_; };

	void SetText(const std::string& text_val) { text_val_ = text_val; };
	std::string GetText() const { return text_val_; };
private:
	std::string text_val_;
	SDL_Color text_color_;
	SDL_Texture* texture_;

	int width_;
	int height_;
};

class ButtonObject : public BaseObject {
#define BUTTON_FRAME_NUM 1
private:
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[BUTTON_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	int type_move_;
	int animation_a_;
	int animation_b_;
	int is_catched_;
	int ScoreRing_;
	int is_Vertical_;
	string addressImgButton_;
public:
	void SetClips();

	bool LoadImage(std::string path, SDL_Renderer* Screen);

	void ShowImage(SDL_Renderer* des);

	string getLinkImgButton() { return addressImgButton_; }

	int getWidthButton() { return width_frame_; }

	int getHeightButton() { return height_frame_; }

	SDL_Rect getSizeButton() { return frame_clip_[0]; }
};

class InfoPlayer {
public:
	InfoPlayer();
	~InfoPlayer();
	void setnamePlayer(string namePlayer) {
		this->namePlayer = namePlayer;
	}

	string getnamePlayer() {
		return namePlayer;
	}
	void setScore(int score) {
		this->score = score;
	}
	
	int getScore() { return score; };

	void setlife(int life) {
		this->life = life;
	}

	int getlife() { return life; };	
private:
	string namePlayer;
	int score;
	int life;
};

#endif