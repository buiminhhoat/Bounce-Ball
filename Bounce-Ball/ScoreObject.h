#ifndef SCORE__OBJECT__H_
#define SCORE__OBJECT__H_

class ScoreObject : public BaseObject {
public:
	ScoreObject();
	~ScoreObject();
	void IncreaseScore(const int& valIncrease) {
		Score += valIncrease;
	};
	int GetScore() { return Score; };
private:
	int Score;
};

#endif