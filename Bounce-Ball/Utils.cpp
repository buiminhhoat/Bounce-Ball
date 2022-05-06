#include "Utils.h"

void MouseEvents::mouseHandleEvent() {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	setPosition(mouseX, mouseY);
}

void MouseEvents::setPosition(int mouseX, int mouseY) {
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}

bool MouseEvents::checkMouseInButton(ButtonObject* button) {
	SDL_Rect rect = button->getRect();

	if (mouseX < rect.x
		|| mouseX > rect.x + rect.w - EPS_PIXELS_IMPACT
		|| mouseY < rect.y
		|| mouseY > rect.y + rect.h - EPS_PIXELS_IMPACT) return false;

	return true;
}