#ifndef __BASEOBJECT__
#define __BASEOBJECT__

#include "CommonFunc.h"

class BaseObject {
public:
	BaseObject();
	~BaseObject();

	void setRectPos(const int& x, const int& y) {
		Rect_.x = x;
		Rect_.y = y;
	}

	void setRectSize(const int& w, const int& h) {
		Rect_.w = w;
		Rect_.h = h;
	}

	SDL_Rect GetRect() const {
		return Rect_;
	}

	SDL_Texture* GetObject() const {
		return Object_;
	}
	
	virtual bool LoadImage(std::string path, SDL_Renderer* screen);

	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	void CleanUp();

protected:
	SDL_Texture* Object_;
	SDL_Rect Rect_;
};
#endif#pragma once
