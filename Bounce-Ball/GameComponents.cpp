#include "GameComponents.h"

LifeObject::LifeObject() {
	widthFrame = 0;
	heightFrame = 0;
	xVal = 0.0;
	yVal = 0.0;
	xPos = 0.0;
	yPos = 0.0;
	onGround = false;
	comeBackTime = 0;
	frame = 0;
	animationA = 0;
	animationB = 0;
	isCatched = 0;
	scoreLife = 0;
	isVertical = 0;
	life = 0;
}

LifeObject::~LifeObject() {
	cleanUp();
}

bool LifeObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret) {
		widthFrame = rect.w / LIFE_FRAME_NUM;
		heightFrame = rect.h;
	}
	return ret;
}

void LifeObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < LIFE_FRAME_NUM; ++i) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;
		}
	}
}

void LifeObject::showImage(SDL_Renderer* des) {
	if (comeBackTime == 0) {
		rect.x = xPos - mapX;
		rect.y = yPos - mapY;
		++frame;
		if (frame >= LIFE_FRAME_NUM) {
			frame = 0;
		}

		SDL_Rect rendQuad = { rect.x, rect.y, widthFrame, heightFrame };
		SDL_RenderCopy(des, object, &frameClip[frame], &rendQuad);
	}
}

RingsObject::RingsObject() {
	widthFrame = 0;
	heightFrame = 0;
	xVal = 0.0;
	yVal = 0.0;
	xPos = 0.0;
	yPos = 0.0;
	onGround = false;
	comeBackTime = 0;
	frame = 0;
	animationA = 0;
	animationB = 0;
	isCatched = 0;
	scoreRing = 0;
	isVertical = 0;
}

RingsObject::~RingsObject() {
	cleanUp();
}

bool RingsObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret) {
		widthFrame = rect.w / RINGS_FRAME_NUM;
		heightFrame = rect.h;
	}
	return ret;
}

void RingsObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < RINGS_FRAME_NUM; ++i) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;
		}
	}
}

void RingsObject::showImage(SDL_Renderer* des) {
	if (comeBackTime == 0) {
		rect.x = xPos - mapX;
		rect.y = yPos - mapY;
		++frame;
		if (frame >= RINGS_FRAME_NUM) {
			frame = 0;
		}

		SDL_Rect rendQuad = { rect.x, rect.y, widthFrame, heightFrame };
		SDL_RenderCopy(des, object, &frameClip[frame], &rendQuad);
	}
}

ScoreObject::ScoreObject() {
	score = 0;
}

ScoreObject::~ScoreObject() {
	cleanUp();
}

EndpointObject::EndpointObject() {
	widthFrame = 0;
	heightFrame = 0;
	xVal = 0.0;
	yVal = 0.0;
	xPos = 0.0;
	yPos = 0.0;
	onGround = false;
	comeBackTime = 0;
	frame = 0;
	animationA = 0;
	animationB = 0;
	isOpened = 0;
	scoreEndpoint = 0;
}

EndpointObject::~EndpointObject() {
	cleanUp();
}

bool EndpointObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret) {
		widthFrame = rect.w / ENDPOINT_FRAME_NUM;
		heightFrame = rect.h;
	}
	return ret;
}

void EndpointObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < ENDPOINT_FRAME_NUM; ++i) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;
		}
	}
}

void EndpointObject::showImage(SDL_Renderer* des) {
	if (comeBackTime == 0) {
		rect.x = xPos - mapX;
		rect.y = yPos - mapY;
		++frame;
		if (frame >= ENDPOINT_FRAME_NUM) {
			frame = 0;
		}

		SDL_Rect rendQuad = { rect.x, rect.y, widthFrame, heightFrame };
		SDL_RenderCopy(des, object, &frameClip[frame], &rendQuad);
	}
}

ThreatsObject::ThreatsObject() {
	widthFrame = 0;
	heightFrame = 0;
	xVal = 0.0;
	yVal = 0.0;
	xPos = 0.0;
	yPos = 0.0;
	onGround = false;
	comeBackTime = 0;
	frame = 0;
	animationA = 0;
	animationB = 0;
	inputType.left = 0;
	typeMove = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject() {
	cleanUp();
}

bool ThreatsObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret) {
		widthFrame = rect.w / THREAT_FRAME_NUM;
		heightFrame = rect.h;
	}
	return ret;
}

void ThreatsObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < THREAT_FRAME_NUM; ++i) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;
		}
	}
}

void ThreatsObject::showImage(SDL_Renderer* des) {
	if (comeBackTime == 0) {
		rect.x = xPos - mapX;
		rect.y = yPos - mapY;
		++frame;
		if (frame >= THREAT_FRAME_NUM) {
			frame = 0;
		}

		SDL_Rect rendQuad = { rect.x, rect.y, widthFrame, heightFrame };
		SDL_RenderCopy(des, object, &frameClip[frame], &rendQuad);
	}
}

void ThreatsObject::initThreats() {
	xVal = 0;
	yVal = 0;
	//if (yPos > 256) {
	//	yPos -= 256;
	//	animationA -= 256;
	//	animationB -= 256;
	//}
	//else {
	//	yPos = 0;
	//}
	xPos = 0;
	comeBackTime = 0;
	inputType.up = 1;
}

void ThreatsObject::doPlayer(Map* gMap) {
	if (typeMove == STATIC_THREAT) return;
	xVal = 0;
	yVal += THREAT_GRAVITY_SPEED;
	if (yVal >= THREAT_MAX_FALL_SPEED) {
		yVal = THREAT_MAX_FALL_SPEED;
	}

	if (inputType.up == 1) {
		yVal -= THREAT_SPEED;
	}
	else if (inputType.down == 1) {
		yVal += THREAT_SPEED;
	}
	checkToMap(gMap);
}

void ThreatsObject::checkToMap(Map* gMap) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	// Check horizontal
	int height_min = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;

	x1 = (xPos + xVal) / TILE_SIZE;
	x2 = (xPos + xVal + widthFrame - 1) / TILE_SIZE;

	y1 = (yPos) / TILE_SIZE;
	y2 = (yPos + heightFrame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (xVal > 0) {
			if (gMap->block[y1][x2] != BLANK_TILES || gMap->block[y2][x2] != BLANK_TILES) {
				xPos = x2 * TILE_SIZE;
				xPos -= widthFrame;
				xVal = 0;
			}
		}
		else {
			if (gMap->block[y1][x1] != BLANK_TILES || gMap->block[y2][x1] != BLANK_TILES) {
				xPos = (x1 + 1) * TILE_SIZE;
				xVal = 0;
			}
		}
	}

	// Check vertical
	int width_min = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
	x1 = xPos / TILE_SIZE;
	x2 = (xPos + width_min) / TILE_SIZE;

	y1 = (yPos + yVal) / TILE_SIZE;
	y2 = (yPos + yVal + heightFrame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (yVal > 0) {
			if (gMap->block[y2][x1] != BLANK_TILES || gMap->block[y2][x2] != BLANK_TILES) {
				yPos = y2 * TILE_SIZE;
				yPos -= (heightFrame);
				yVal = 0;
				onGround = true;
				if (typeMove == TypeMove::MOVE_IN_SPACE_THREAT) {
					inputType.down = 0;
					inputType.up = 1;
				}
			}
		}
		else if (yVal < 0) {
			if (gMap->block[y1][x1] != BLANK_TILES || gMap->block[y1][x2] != BLANK_TILES) {
				yPos = (y1 + 1) * TILE_SIZE;
				yVal = 0;
				if (typeMove == TypeMove::MOVE_IN_SPACE_THREAT) {
					inputType.down = 1;
					inputType.up = 0;
				}
			}
		}
	}

	xPos += xVal;
	yPos += yVal;

	if (xPos < 0) {
		xPos = 0;
	}
	else if (xPos + widthFrame > gMap->maxX) {
		xPos = gMap->maxX - widthFrame - 1;
	}

	if (yPos < 0) {
		yPos = THREAT_SPEED;
		inputType.up = 0;
		inputType.down = 1;
	}
	if (yPos > gMap->maxY) {
		comeBackTime = 10;
	}
}

void ThreatsObject::impMoveType(SDL_Renderer* screen) {
	if (typeMove == STATIC_THREAT) {
		;
	}
	else {
		if (yPos > animationB) {
			inputType.up = 1;
			inputType.down = 0;
			loadImage("img//threats//dyn_thorn.png", screen);
		}
		else if (yPos < animationA) {
			inputType.up = 0;
			inputType.down = 1;
			loadImage("img//threats//dyn_thorn.png", screen);
		}
	}
}

CheckpointObject::CheckpointObject() {
	widthFrame = 0;
	heightFrame = 0;
	xVal = 0.0;
	yVal = 0.0;
	xPos = 0.0;
	yPos = 0.0;
	onGround = false;
	comeBackTime = 0;
	frame = 0;
	animationA = 0;
	animationB = 0;
	isCatched = 0;
	scoreRing = 0;
	isVertical = 0;
}

CheckpointObject::~CheckpointObject() {
	cleanUp();
}

bool CheckpointObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret) {
		widthFrame = rect.w / CHECKPOINT_FRAME_NUM;
		heightFrame = rect.h;
	}
	return ret;
}

void CheckpointObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < CHECKPOINT_FRAME_NUM; ++i) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;
		}
	}
}

void CheckpointObject::showImage(SDL_Renderer* des) {
	if (comeBackTime == 0) {
		rect.x = xPos - mapX;
		rect.y = yPos - mapY;
		++frame;
		if (frame >= CHECKPOINT_FRAME_NUM) {
			frame = 0;
		}

		SDL_Rect rendQuad = { rect.x, rect.y, widthFrame, heightFrame };
		SDL_RenderCopy(des, object, &frameClip[frame], &rendQuad);
	}
}

LTexture::LTexture() {
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	texture = NULL;
	textVal = "";
	width = 0;
	height = 0;
}

LTexture::~LTexture() {
	cleanUp();
}

bool LTexture::loadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
	cleanUp();
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, textVal.c_str(), textColor);
	if (text_surface != NULL) {
		texture = SDL_CreateTextureFromSurface(screen, text_surface);
		width = text_surface->w;
		height = text_surface->h;
		SDL_FreeSurface(text_surface);
	}
	else {
		printf("Unable to create texture from %s! SDL Error: %s\n", textVal.c_str(), SDL_GetError());
	}
	return (text_surface != NULL);
}

void LTexture::cleanUp() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
}

void LTexture::setColor(int type) {
	if (type == RED_COLOR) {
		SDL_Color color = { 255, 0, 0 };
		textColor = color;
	}
	if (type == ORANGE_COLOR) {
		SDL_Color color = { 255, 165, 0 };
		textColor = color;
	}
	if (type == YELLOW_COLOR) {
		SDL_Color color = { 255, 255, 0 };
		textColor = color;
	}
	if (type == GREEN_COLOR) {
		SDL_Color color = { 0, 255, 0 };
		textColor = color;
	}
	if (type == BLUE_COLOR) {
		SDL_Color color = { 0, 0, 255 };
		textColor = color;
	}
	if (type == INDIGO_COLOR) {
		SDL_Color color = { 75, 0, 130 };
		textColor = color;
	}
	if (type == PURPLE_COLOR) {
		SDL_Color color = { 128, 0, 128 };
		textColor = color;
	}
	if (type == WHITE_COLOR) {
		SDL_Color color = { 255, 255, 255 };
		textColor = color;
	}
	if (type == BLACK_COLOR) {
		SDL_Color color = { 0, 0, 0 };
		textColor = color;
	}
}

void LTexture::showText(SDL_Renderer* screen,
	float xPosText, float yPosText,
	SDL_Rect* clip /* = NULL */,
	double angle /* = 0.0 */,
	SDL_Point* center /* = NULL */,
	SDL_RendererFlip flip /* = SDL_FLIP_NONE */) {
	SDL_Rect renderQuad = { xPosText, yPosText, width, height };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
	cleanUp();
}

ButtonObject::ButtonObject() {
	widthFrame = 0;
	heightFrame = 0;
	xVal = 0.0;
	yVal = 0.0;
	xPos = 0.0;
	yPos = 0.0;
	frame = 0;
	isUnlock = 1;
}

ButtonObject::~ButtonObject() {
	cleanUp();
}

bool ButtonObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret) {
		widthFrame = rect.w / BUTTON_FRAME_NUM;
		heightFrame = rect.h;
	}
	return ret;
}

void ButtonObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < BUTTON_FRAME_NUM; ++i) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;
		}
	}
}

void ButtonObject::showImage(SDL_Renderer* des) {
	rect.x = xPos - mapX;
	rect.y = yPos - mapY;
	++frame;
	if (frame >= CHECKPOINT_FRAME_NUM) {
		frame = 0;
	}

	SDL_Rect rendQuad = { rect.x, rect.y, widthFrame, heightFrame };
	SDL_RenderCopy(des, object, &frameClip[frame], &rendQuad);
}

InfoPlayer::InfoPlayer() {
	username = "";
	password = "";
	score = 0;
	yourHighScore = 0;
	level = 0;
	life = ORIGINAL_LIFE;
	for (int i = 0; i < 55; ++i) unlockLevel[i] = 0;
}

InfoPlayer::~InfoPlayer() {

}