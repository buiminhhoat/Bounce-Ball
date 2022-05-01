#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

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
	int isCatched;
	int scoreLife;
	int isVertical;
	int life;
};

class RingsObject : public BaseObject {
#define SCORE_RING_HORIZONTAL 50
#define SCORE_RING_VERTICAL 100 
public:
	RingsObject();
	~RingsObject();
	int getIsCatched() { return isCatched; };
	void setIsCatched(const int& isCatched) { this->isCatched = isCatched; };

	int getScoreRing() { return scoreRing; };
	void setScoreRing(const int& scoreRing) { this->scoreRing = scoreRing; };

	int getIsVertical() { return isVertical; };
	void setIsVertical(const int& isVertical) { this->isVertical = isVertical; };
private:
	int isCatched;
	int scoreRing;
	int isVertical;
};

class ScoreObject : public BaseObject {
public:
	ScoreObject();
	~ScoreObject();
	void increaseScore(const int& valIncrease) {
		this->score += valIncrease;
	};
	int getScore() { return this->score; };
	void setScore(const int &score) { this->score = score; }

	void setYourHighScore(int yourHighscore) { this->yourHighscore = yourHighscore; };
	int getYourHighScore() { return this->yourHighscore; };
private:
	int score;
	int yourHighscore;
};

class EndpointObject : public BaseObject {
#define SCORE_ENDPOINT 50
public:
	EndpointObject();
	~EndpointObject();

	int getIsOpened() { return isOpened; };
	void setIsOpened(const int& isOpened) { this->isOpened = isOpened; };

	int getScoreEndpoint() { return this->scoreEndpoint; };
	void setScoreEndpoint(const int& scoreEndpoint) { this->scoreEndpoint = scoreEndpoint; };
	
private:
	int isOpened;
	int scoreEndpoint;
};

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

class CheckpointObject : public BaseObject {
#define SCORE_CHECKPOINT 25
public:
	CheckpointObject();
	~CheckpointObject();

	int getIsCatched() { return this->isCatched; };
	void setIsCatched(const int& isCatched) { this->isCatched = isCatched; };

	int getScoreRing() { return scoreRing; };
	void setScoreRing(const int& scoreRing) { this->scoreRing = scoreRing; };

	int getIsVertical() { return this->isVertical; };
	void setIsVertical(const int& isVertical) { this->isVertical = isVertical; };
private:
	int isCatched;
	int scoreRing;
	int isVertical;
};

class LTexture {
public:
	LTexture();
	~LTexture();

	enum COLOR {
		RED_COLOR,
		ORANGE_COLOR,
		YELLOW_COLOR,
		GREEN_COLOR,
		BLUE_COLOR,
		INDIGO_COLOR,
		PURPLE_COLOR,
		WHITE_COLOR,
		BLACK_COLOR,
	};

	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void cleanUp();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setColor(int type);
	void showText(SDL_Renderer* screen,
		float xPosText, float yPosText,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setPosX(float posX) { this->posX = posX; };
	void setPosY(float posY) { this->posY = posY; };

	float getPosX() { return this->posX; };
	float getPosY() { return this->posY; };

	float getWidth() { return this->width; };
	float getHeight() { return this->height; };

	void setWidth(float width) { this->width = width; };
	void setHeight(float height) { this->height = height; };
	void setText(const std::string& textVal) { this->textVal = textVal; };
	std::string getText() const { return this->textVal; };

private:
	std::string textVal;
	SDL_Color textColor;
	SDL_Texture* texture;

	float width;
	float height;
	float posX;
	float posY;
};

class ButtonObject : public BaseObject {
public:
	ButtonObject();
	~ButtonObject();

	string getLinkImgButton() { return addressImgButton; }

	void setIsUnlock(const int& isUnlock) { this->isUnlock = isUnlock; };
	int getIsUnlock() { return this->isUnlock; };
private:
	string addressImgButton;
	int isUnlock;
};

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
	void setUnlockLevel(int level, int value) { unlockLevel[level] = value; };
	int getUnlockLevel(int level) { return unlockLevel[level]; };
	void setSound(int sound) { this->sound = sound; };
	int getSound() { return this->sound; };
private:
	string username;
	string password;
	int score;
	int life;
	int level;
	int yourHighScore;
	int unlockLevel[MAX_LEVEL + FIX_ZERO_INDEX];
	int sound;
};

#endif