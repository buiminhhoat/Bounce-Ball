#ifndef __MOUSE__
#define __MOUSE__

#include "GameComponents.h"

using namespace std;

class Mouse : public BaseObject {
private:
	int mouseX;
	int mouseY;
	void setPosition(int mouseX, int mouseY);
public:
	Mouse() {
		loadImage("Resources/Image/MouseCursor/MouseCursor.png", gScreen);
		rect.w = 38;
		rect.h = 53;
		SDL_ShowCursor(false);
	}
	void mouseHandleEvent();
	bool checkMouseInButton(ButtonObject* button);
	void render(SDL_Renderer* des) {
		SDL_RenderCopy(des, object, NULL, &rect);
	}
};

#endif
