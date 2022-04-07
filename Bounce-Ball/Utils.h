#ifndef __UTILS__
#define __UTILS__

#include "GameComponents.h"

using namespace std;

class MouseEvents {
private:
    int mouse_x;
    int mouse_y;
    void setPosition(int x, int y);
public:
    void mouseHandleEvent();
    bool CheckMouseInButton(ButtonObject* button);
};

#endif // __UTILS__
#pragma once
