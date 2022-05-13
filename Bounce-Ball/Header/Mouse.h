#ifndef __MOUSE__
#define __MOUSE__

#include "GameComponents.h"

using namespace std;

class MouseEvents : public BaseObject {
private:
	int mouseX;
	int mouseY;
	void setPosition(int mouseX, int mouseY);
	SDL_Rect point;
public:
	MouseEvents() {
		loadImage("Resources/Image/MouseCursor/MouseCursor.png", gScreen);
		rect.w = 25;
		rect.h = 25;
		point.h = 1;
		point.w = 1;
		SDL_ShowCursor(false);
	}
	void mouseHandleEvent();
	bool checkMouseInButton(ButtonObject* button);
	void render(SDL_Renderer* des) {
		SDL_RenderCopy(des, object, NULL, &rect);
	}
};

#endif
