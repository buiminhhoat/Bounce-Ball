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
		xPos = x;
		yPos = y;
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

	void setXVal(const float& xVal) { this->xVal = xVal; }
	void setYVal(const float& yVal) { this->yVal = yVal; }

	void setXPos(const float& xPos) { rect.x = xPos; this->xPos = xPos; }
	void setYPos(const float& yPos) { rect.y = yPos; this->yPos = yPos; }

	float getXPos() const { return rect.x; }
	float getYPos() const { return rect.y; }

	void setMapXY(const int& mapX, const int& mapY) { this->mapX = mapX; this->mapY = mapY; }

	int getWidth() const { return rect.w; };
	int getHeight() const { return rect.h; };

	bool loadImage(std::string path, SDL_Renderer* screen);

	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	void cleanUp();
protected:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	SDL_Texture* object;
	SDL_Rect rect;
};
#endif#pragma once
