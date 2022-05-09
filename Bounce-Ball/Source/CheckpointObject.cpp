#include "../Header/CheckpointObject.h"

CheckpointObject::CheckpointObject() {
	isCatched = false;
	scoreRing = 0;
	isVertical = false;
}

CheckpointObject::~CheckpointObject() {
	cleanUp();
}
