#ifndef __LIFEOBJECT__
#define __LIFEOBJECT__

#include "BaseObject.h"
#include "GameMap.h"

using namespace std;

class LifeObject : public BaseObject {
#define SCORE_LIFE 50
public:
	LifeObject();
	~LifeObject();

	void increaseLife(const int& valIncrease) {
		this->life += valIncrease;
	};

	int getLife() { return this->life; };

	void SetLife(const int& life) {
		this->life = life;
	}

	int getIsCatched() { return this->isCatched; };
	void setIsCatched(const int& isCatched) { this->isCatched = isCatched; };

	int getScoreLife() { return this->scoreLife; };
	void setScoreLife(const int& scoreLife) { this->scoreLife = scoreLife; };

	int getIsVertical() { return this->isVertical; };
	void setIsVertical(const int& isVertical) { this->isVertical = isVertical; };
private:
	bool isCatched;
	int scoreLife;
	bool isVertical;
	int life;
};

#endif