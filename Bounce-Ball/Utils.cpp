#include "Utils.h"

void MouseEvents::mouseHandleEvent() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setPosition(x, y);
}

void MouseEvents::setPosition(int x, int y) {
    this->mouse_x = x;
    this->mouse_y = y;
}

bool MouseEvents::CheckMouseInButton(ButtonObject* button) {
    SDL_Rect rect = button->GetRect();

    if (mouse_x < rect.x
            || mouse_x > rect.x + rect.w - 1
            || mouse_y < rect.y
            || mouse_y > rect.y + rect.h - 1) return false;

    return true;
}
