#ifndef __MOUSE__
#define __MOUSE__

#include "GameComponents.h"

using namespace std;

class Mouse {
private:
	int mouseX;
	int mouseY;
	void setPosition(int mouseX, int mouseY);
public:
	void mouseHandleEvent();
	bool checkMouseInButton(ButtonObject* button);
};

#endif
