#ifndef LIFE__OBJECT__H_
#define LIFE__OBJECT__H_

#define ORIGINAL_LIFE 3
#define LIFE_FRAME_NUM 1
#define SCORE_LIFE 50

class LifeObject : public BaseObject {
public:
	LifeObject();
	~LifeObject();
	
	void IncreaseLife(const int& valIncrease) {
		Life_ += valIncrease;
	};
	
	int GetLife() { return Life_; };

	void SetLife(const int &Life) {
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

#endif