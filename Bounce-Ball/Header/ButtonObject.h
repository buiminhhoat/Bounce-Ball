#ifndef __BUTTONOBJECT__
#define __BUTTONOBJECT__

#include "BaseObject.h"
#include "GameMap.h"

using namespace std;

class ButtonObject : public BaseObject {
public:
	ButtonObject();
	~ButtonObject();

	string getLinkImgButton() { return addressImgButton; }

	void setIsUnlock(const bool& isUnlock) { this->isUnlock = isUnlock; };
	int getIsUnlock() { return this->isUnlock; };
private:
	string addressImgButton;
	bool isUnlock;
};

#endif