#include "../Header/ScoreObject.h"

ScoreObject::ScoreObject() {
	score = 0;
}

ScoreObject::~ScoreObject() {
	cleanUp();
}