#include "../Header/ButtonObject.h"

ButtonObject::ButtonObject() {
	isUnlock = true;
}

ButtonObject::~ButtonObject() {
	cleanUp();
}