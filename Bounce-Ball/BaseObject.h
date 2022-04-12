#ifndef __BASEOBJECT__
#define __BASEOBJECT__

#include "CommonFunc.h"

class BaseObject {
public:
	BaseObject();
	~BaseObject();

	void setRectPos(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}

	void setRectSize(const int& w, const int& h) {
		rect.w = w;
		rect.h = h;
	}

	SDL_Rect getRect() const {
		return rect;
	}

	SDL_Texture* getObject() const {
		return object;
	}
	
	virtual bool loadImage(std::string path, SDL_Renderer* screen);

	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	void cleanUp();

protected:
	SDL_Texture* object;
	SDL_Rect rect;
};
#endif#pragma once
