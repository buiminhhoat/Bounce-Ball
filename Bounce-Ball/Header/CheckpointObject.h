#ifndef __CHECKPOINTOBJECT__
#define __CHECKPOINTOBJECT__

#include "BaseObject.h"
#include "GameMap.h"

using namespace std;

class CheckpointObject : public BaseObject {
#define SCORE_CHECKPOINT 25
public:
	CheckpointObject();
	~CheckpointObject();

	bool getIsCatched() { return this->isCatched; };
	void setIsCatched(const bool& isCatched) { this->isCatched = isCatched; };

	int getScoreRing() { return scoreRing; };
	void setScoreRing(const int& scoreRing) { this->scoreRing = scoreRing; };

	int getIsVertical() { return this->isVertical; };
	void setIsVertical(const int& isVertical) { this->isVertical = isVertical; };
private:
	bool isCatched;
	int scoreRing;
	bool isVertical;
};

#endif