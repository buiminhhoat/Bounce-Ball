#include "../Header/LifeObject.h"

LifeObject::LifeObject() {
	isCatched = false;
	scoreLife = 0;
	isVertical = false;
	life = 0;
}

LifeObject::~LifeObject() {
	cleanUp();
}
