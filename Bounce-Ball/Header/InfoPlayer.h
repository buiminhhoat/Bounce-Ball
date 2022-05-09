#ifndef __INFOPLAYER__
#define __INFOPLAYER__

#include "BaseObject.h"
#include "GameMap.h"

using namespace std;

class InfoPlayer {
public:
	InfoPlayer();
	~InfoPlayer();

	void setScore(int score) {
		this->score = score;
	}

	int getScore() { return this->score; };

	void setlife(int life) {
		this->life = life;
	}

	int getLife() { return this->life; };

	void setLevel(int level) {
		this->level = level;
	}

	int getLevel() {
		return this->level;
	}

	void setUsername(string username) { this->username = username; };
	string getUsername() { return this->username; };
	void setPassword(string password) { this->password = password; };
	string getPassword() { return this->password; };
	void setYourHighScore(int yourHighScore) { this->yourHighScore = yourHighScore; };
	int getYourHighScore() { return this->yourHighScore; };
	void setUnlockLevel(int level, bool value) { unlockLevel[level] = value; };
	bool getUnlockLevel(int level) { return unlockLevel[level]; };
	void setSound(bool sound) { this->sound = sound; };
	bool getSound() { return this->sound; };
private:
	string username;
	string password;
	int score;
	int life;
	int level;
	int yourHighScore;
	bool unlockLevel[MAX_LEVEL + FIX_ZERO_INDEX];
	bool sound;
};

#endif