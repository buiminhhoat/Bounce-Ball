#ifndef __UTILS__
#define __UTILS__

#include "GameComponents.h"

using namespace std;

class MouseEvents {
private:
	int mouseX;
	int mouseY;
	void setPosition(int mouseX, int mouseY);
public:
	void mouseHandleEvent();
	bool checkMouseInButton(ButtonObject* button);
};

#endif // __UTILS__
#pragma once
