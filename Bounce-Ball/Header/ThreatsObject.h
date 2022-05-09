#ifndef __THREATSOBJECT__
#define __THREATSOBJECT__

#include "BaseObject.h"
#include "GameMap.h"

using namespace std;

class ThreatsObject : public BaseObject {
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 1
public:
	ThreatsObject();
	~ThreatsObject();

	enum TypeMove {
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
	};

	void doPlayer(Map* gMap);
	void checkToMap(Map* gMap);
	void setTypeMove(const int& typeMove) { this->typeMove = typeMove; };
	void setAnimationPos(const int& animationA, const int& animationB) {
		this->animationA = animationA;
		this->animationB = animationB;
	};
	void setInputUp(const int& up) { inputType.up = up; };
	void impMoveType(SDL_Renderer* screen);
private:
	bool onGround;
	int frame;
	int typeMove;
	int animationA;
	int animationB;
	actionType inputType;
};

#endif