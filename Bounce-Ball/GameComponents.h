#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

#include "BaseObject.h"
#include "GameMap.h"

using namespace std;

class LifeObject : public BaseObject {
	#define ORIGINAL_LIFE 10000
	#define LIFE_FRAME_NUM 1 
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

	void setXVal(const float& xVal) { this->xVal = xVal; }
	void setYVal(const float& yVal) { this->yVal = yVal; }

	void setXPos(const float& xPos) { this->xPos = xPos; }
	void setYPos(const float& yPos) { this->yPos = yPos; }

	float getXPos() const { return this->xPos; }
	float getYPos() const { return this->yPos; }

	void setMapXY(const int& mapX, const int& mapY) { this->mapX = mapX; this->mapY = mapY; }

	void setClips();

	bool loadImage(std::string path, SDL_Renderer* screen);

	void showImage(SDL_Renderer* des);

	int getWidthFrame() const { return this->widthFrame; };
	int getHeightFrame() const { return this->heightFrame; };

	void setTypeMove(const int& typeMove) { this->typeMove = typeMove; };
	void setAnimationPos(const int& animationA, const int& animationB) {
		this->animationA = animationA;
		this->animationB = animationB;
	};

	int getIsCatched() { return this->isCatched; };
	void setIsCatched(const int& isCatched) { this->isCatched = isCatched; };

	int getScoreLife() { return this->scoreLife; };
	void setScoreLife(const int& scoreLife) { this->scoreLife = scoreLife; };

	int getIsVertical() { return this->isVertical; };
	void setIsVertical(const int& isVertical) { this->isVertical = isVertical; };
private:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	bool onGround;
	int comeBackTime;
	SDL_Rect frameClip[LIFE_FRAME_NUM];
	int widthFrame;
	int heightFrame;
	int frame;
	int typeMove;
	int animationA;
	int animationB;
	int isCatched;
	int scoreLife;
	int isVertical;
	int life;
};

class RingsObject : public BaseObject {
#define RINGS_FRAME_NUM 1
#define SCORE_RING_HORIZONTAL 50
#define SCORE_RING_VERTICAL 100 
public:
	RingsObject();
	~RingsObject();

	void setXVal(const float& xVal) { this->xVal = xVal; }
	void setYVal(const float& yVal) { this->yVal = yVal; }

	void setXPos(const float& xPos) { this->xPos = xPos; }
	void setYPos(const float& yPos) { this->yPos = yPos; }

	float getXPos() const { return this->xPos; }
	float getYPos() const { return this->yPos; }

	void setMapXY(const int& mapX, const int& mapY) { this->mapX = mapX; this->mapY = mapY; }

	void setClips();

	bool loadImage(std::string path, SDL_Renderer* screen);

	void showImage(SDL_Renderer* des);

	int getWidthFrame() const { return widthFrame; };
	int getHeightFrame() const { return heightFrame; };

	void setTypeMove(const int& typeMove) { this->typeMove = typeMove; };
	void setAnimationPos(const int& animationA, const int& animationB) {
		this->animationA = animationA;
		this->animationB = animationB;
	};

	int getIsCatched() { return isCatched; };
	void setIsCatched(const int& isCatched) { this->isCatched = isCatched; };

	int getScoreRing() { return scoreRing; };
	void setScoreRing(const int& scoreRing) { this->scoreRing = scoreRing; };

	int getIsVertical() { return isVertical; };
	void setIsVertical(const int& isVertical) { this->isVertical = isVertical; };
private:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	bool onGround;
	int comeBackTime;
	SDL_Rect frameClip[RINGS_FRAME_NUM];
	int widthFrame;
	int heightFrame;
	int frame;
	int typeMove;
	int animationA;
	int animationB;
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
#define ENDPOINT_FRAME_NUM 1
#define SCORE_ENDPOINT 50
public:
	EndpointObject();
	~EndpointObject();

	void setXVal(const float& xVal) { this->xVal = xVal; }
	void setYVal(const float& yVal) { this->yVal = yVal; }

	void setXPos(const float& xPos) { this->xPos = xPos; }
	void setYPos(const float& yPos) { this->yPos = yPos; }

	float getXPos() const { return this->xPos; }
	float getYPos() const { return this->yPos; }

	void setMapXY(const int& mapX, const int& mapY) { this->mapX = mapX; this->mapY = mapY; }

	void setClips();

	bool loadImage(std::string path, SDL_Renderer* screen);

	void showImage(SDL_Renderer* des);

	int getWidthFrame() const { return widthFrame; };
	int getHeightFrame() const { return heightFrame; };

	void setTypeMove(const int& typeMove) { this->typeMove = typeMove; };
	void setAnimationPos(const int& animationA, const int& animationB) {
		this->animationA = animationA;
		this->animationB = animationB;
	};

	int getIsOpened() { return isOpened; };
	void setIsOpened(const int& isOpened) { this->isOpened = isOpened; };

	int getScoreEndpoint() { return this->scoreEndpoint; };
	void setScoreEndpoint(const int& scoreEndpoint) { this->scoreEndpoint = scoreEndpoint; };
	
private:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	bool onGround;
	int comeBackTime;
	SDL_Rect frameClip[ENDPOINT_FRAME_NUM];
	int widthFrame;
	int heightFrame;
	int frame;
	int typeMove;
	int animationA;
	int animationB;
	int isOpened;
	int scoreEndpoint;
};

class ThreatsObject : public BaseObject {
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_FRAME_NUM 1
#define THREAT_SPEED 1
public:
	ThreatsObject();
	~ThreatsObject();

	enum TypeMove {
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
	};

	void setXVal(const float& xVal) { this->xVal = xVal; }
	void setYVal(const float& yVal) { this->yVal = yVal; }

	void setXPos(const float& xPos) { this->xPos = xPos; }
	void setYPos(const float& yPos) { this->yPos = yPos; }

	float getXPos() const { return xPos; }
	float getYPos() const { return yPos; }

	void setMapXY(const int& mapX, const int& mapY) { this->mapX = mapX; this->mapY = mapY; }

	void setClips();

	bool loadImage(std::string path, SDL_Renderer* screen);

	void showImage(SDL_Renderer* des);

	int getWidthFrame() const { return widthFrame; };
	int getHeightFrame() const { return heightFrame; };

	void doPlayer(Map* gMap);
	void checkToMap(Map* gMap);
	void initThreats();
	void setTypeMove(const int& typeMove) { this->typeMove = typeMove; };
	void setAnimationPos(const int& animationA, const int& animationB) {
		this->animationA = animationA;
		this->animationB = animationB;
	};
	void setInputUp(const int& up) { inputType.up = up; };
	void impMoveType(SDL_Renderer* screen);
private:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	bool onGround;
	int comeBackTime;
	SDL_Rect frameClip[THREAT_FRAME_NUM];
	int widthFrame;
	int heightFrame;
	int frame;
	int typeMove;
	int animationA;
	int animationB;
	Input inputType;
};

class CheckpointObject : public BaseObject {
#define CHECKPOINT_FRAME_NUM 1
#define SCORE_CHECKPOINT 25
public:
	CheckpointObject();
	~CheckpointObject();

	void setXVal(const float& xVal) { this->xVal = xVal; }
	void setYVal(const float& yVal) { this->yVal = yVal; }

	void setXPos(const float& xPos) { this->xPos = xPos; }
	void setYPos(const float& yPos) { this->yPos = yPos; }

	float getXPos() const { return xPos; }
	float getYPos() const { return yPos; }

	void setMapXY(const int& mapX, const int& mapY) { this->mapX = mapX; this->mapY = mapY; }

	void setClips();

	bool loadImage(std::string path, SDL_Renderer* screen);

	void showImage(SDL_Renderer* des);

	int getWidthFrame() const { return widthFrame; };
	int getHeightFrame() const { return heightFrame; };

	void setTypeMove(const int& typeMove) { this->typeMove = typeMove; };
	void setAnimationPos(const int& animationA, const int& animationB) {
		this->animationA = animationA;
		this->animationB = animationB;
	};

	int getIsCatched() { return this->isCatched; };
	void setIsCatched(const int& isCatched) { this->isCatched = isCatched; };

	int getScoreRing() { return scoreRing; };
	void setScoreRing(const int& scoreRing) { this->scoreRing = scoreRing; };

	int getIsVertical() { return this->isVertical; };
	void setIsVertical(const int& isVertical) { this->isVertical = isVertical; };
private:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	bool onGround;
	int comeBackTime;
	SDL_Rect frameClip[CHECKPOINT_FRAME_NUM];
	int widthFrame;
	int heightFrame;
	int frame;
	int typeMove;
	int animationA;
	int animationB;
	int isCatched;
	int scoreRing;
	int isVertical;
};

class LTexture {
public:
	LTexture();
	~LTexture();

	enum {
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
#define BUTTON_FRAME_NUM 1
private:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	SDL_Rect frameClip[BUTTON_FRAME_NUM];
	int widthFrame;
	int heightFrame;
	int frame;
	string addressImgButton;
public:
	ButtonObject();
	~ButtonObject();

	void setXVal(const float& xVal) { this->xVal = xVal; }
	void setYVal(const float& yVal) { this->yVal = yVal; }

	void setXPos(const float& xPos) { this->xPos = xPos; }
	void setYPos(const float& yPos) { this->yPos = yPos; }

	float getXPos() const { return this->xPos; }
	float getYPos() const { return this->yPos; }

	void setMapXY(const int& mapX, const int& mapY) { this->mapX = mapX; this->mapY = mapY; }

	void setClips();

	bool loadImage(std::string path, SDL_Renderer* screen);

	void showImage(SDL_Renderer* des);

	string getLinkImgButton() { return addressImgButton; }

	int getWidthButton() { return widthFrame; }

	int getHeightButton() { return heightFrame; }
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
private:
	string username;
	string password;
	int score;
	int life;
	int level;
	int yourHighScore;
	int unlockLevel[55];
};

#endif