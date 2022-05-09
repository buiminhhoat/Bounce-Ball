#include "../Header/RingsObject.h"

RingsObject::RingsObject() {
	isCatched = false;
	scoreRing = 0;
	isVertical = false;
}

RingsObject::~RingsObject() {
	cleanUp();
}

