#ifndef __SCOREOBJECT__
#define __SCOREOBJECT__
#include "BaseObject.h"
#include "GameMap.h"
class ScoreObject : public BaseObject {
public:
	ScoreObject();
	~ScoreObject();
	void increaseScore(const int& valIncrease) {
		this->score += valIncrease;
	};
	int getScore() { return this->score; };
	void setScore(const int& score) { this->score = score; }

	void setYourHighScore(int yourHighscore) { this->yourHighscore = yourHighscore; };
	int getYourHighScore() { return this->yourHighscore; };
private:
	int score;
	int yourHighscore;
};
#endif

