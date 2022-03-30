#ifndef TEXT__OBJECT__H_
#define TEXT__OBJECT__H_

#include "CommonFunc.h"

using namespace std;

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
#endif
#pragma once
