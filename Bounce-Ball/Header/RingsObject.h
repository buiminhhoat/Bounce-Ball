#ifndef __RINGSOBJECT__
#define __RINGSOBJECT__

#include "BaseObject.h"
#include "GameMap.h"

class RingsObject : public BaseObject {
#define SCORE_RING_HORIZONTAL 50
#define SCORE_RING_VERTICAL 100 
public:
	RingsObject();
	~RingsObject();
	bool getIsCatched() { return isCatched; };
	void setIsCatched(const bool& isCatched) { this->isCatched = isCatched; };

	int getScoreRing() { return scoreRing; };
	void setScoreRing(const int& scoreRing) { this->scoreRing = scoreRing; };

	bool getIsVertical() { return isVertical; };
	void setIsVertical(const bool& isVertical) { this->isVertical = isVertical; };
private:
	bool isCatched;
	int scoreRing;
	bool isVertical;
};
#endif