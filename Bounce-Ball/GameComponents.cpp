#include "GameComponents.h"

LifeObject::LifeObject() {
	isCatched = 0;
	scoreLife = 0;
	isVertical = 0;
	life = 0;
}

LifeObject::~LifeObject() {
	cleanUp();
}

RingsObject::RingsObject() {
	isCatched = 0;
	scoreRing = 0;
	isVertical = 0;
}

RingsObject::~RingsObject() {
	cleanUp();
}

ScoreObject::ScoreObject() {
	score = 0;
}

ScoreObject::~ScoreObject() {
	cleanUp();
}

EndpointObject::EndpointObject() {
	isOpened = 0;
	scoreEndpoint = 0;
}

EndpointObject::~EndpointObject() {
	cleanUp();
}

ThreatsObject::ThreatsObject() {
	onGround = false;
	animationA = 0;
	animationB = 0;
	inputType.left = 0;
	typeMove = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject() {
	cleanUp();
}

void ThreatsObject::doPlayer(Map* gMap) {
	if (typeMove == STATIC_THREAT) return;
	xVal = 0;
	yVal += THREAT_GRAVITY_SPEED;
	if (yVal >= THREAT_MAX_FALL_SPEED) {
		yVal = THREAT_MAX_FALL_SPEED;
	}

	if (inputType.up == true) {
		yVal -= THREAT_SPEED;
	}
	else if (inputType.down == true) {
		yVal += THREAT_SPEED;
	}
	checkToMap(gMap);
}

void ThreatsObject::checkToMap(Map* gMap) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int heightFrame = getHeight();
	int widthFrame = getWidth();

	// Check horizontal
	int height_min = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;

	x1 = (xPos + xVal) / TILE_SIZE;
	x2 = (xPos + xVal + widthFrame - EPS_PIXELS_IMPACT) / TILE_SIZE;

	y1 = (yPos) / TILE_SIZE;
	// 1 is eps
	y2 = (yPos + heightFrame - EPS_PIXELS_IMPACT) / TILE_SIZE;

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
	y2 = (yPos + yVal + heightFrame - EPS_PIXELS_IMPACT) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (yVal > 0) {
			if (gMap->block[y2][x1] != BLANK_TILES || gMap->block[y2][x2] != BLANK_TILES) {
				yPos = y2 * TILE_SIZE;
				yPos -= (heightFrame);
				yVal = 0;
				onGround = true;
				if (typeMove == TypeMove::MOVE_IN_SPACE_THREAT) {
					inputType.down = false;
					inputType.up = true;
				}
			}
		}
		else if (yVal < 0) {
			if (gMap->block[y1][x1] != BLANK_TILES || gMap->block[y1][x2] != BLANK_TILES) {
				yPos = (y1 + 1) * TILE_SIZE;
				yVal = 0;
				if (typeMove == TypeMove::MOVE_IN_SPACE_THREAT) {
					inputType.down = true;
					inputType.up = false;
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
		xPos = gMap->maxX - widthFrame - EPS_PIXELS_IMPACT;
	}

	if (yPos < 0) {
		yPos = THREAT_SPEED;
		inputType.up = false;
		inputType.down = true;
	}
}

void ThreatsObject::impMoveType(SDL_Renderer* screen) {
	if (typeMove == STATIC_THREAT) {
		;
	}
	else {
		if (yPos > animationB) {
			inputType.up = true;
			inputType.down = false;
			loadImage("img//threats//dyn_thorn.png", screen);
		}
		else if (yPos < animationA) {
			inputType.up = false;
			inputType.down = true;
			loadImage("img//threats//dyn_thorn.png", screen);
		}
	}
}

CheckpointObject::CheckpointObject() {
	isCatched = 0;
	scoreRing = 0;
	isVertical = 0;
}

CheckpointObject::~CheckpointObject() {
	cleanUp();
}

LTexture::LTexture() {
	/* RGB WHITE */
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
		/* RGB RED */
		SDL_Color color = { 255, 0, 0 };
		textColor = color;
	}
	if (type == ORANGE_COLOR) {
		/* RGB ORANGE */
		SDL_Color color = { 255, 165, 0 };
		textColor = color;
	}
	if (type == YELLOW_COLOR) {
		/* RGB YELLOW */
		SDL_Color color = { 255, 255, 0 };
		textColor = color;
	}
	if (type == GREEN_COLOR) {
		/* RGB GREEN */
		SDL_Color color = { 0, 255, 0 };
		textColor = color;
	}
	if (type == BLUE_COLOR) {
		/* RGB BLUE */
		SDL_Color color = { 0, 0, 255 };
		textColor = color;
	}
	if (type == INDIGO_COLOR) {
		/* RGB INDIGO */
		SDL_Color color = { 75, 0, 130 };
		textColor = color;
	}
	if (type == PURPLE_COLOR) {
		/* RGB PURPLE */
		SDL_Color color = { 128, 0, 128 };
		textColor = color;
	}
	if (type == WHITE_COLOR) {
		/* RGB WHITE */
		SDL_Color color = { 255, 255, 255 };
		textColor = color;
	}
	if (type == BLACK_COLOR) {
		/* RGB BLACK */
		SDL_Color color = { 0, 0, 0 };
		textColor = color;
	}
}

void LTexture::showText(SDL_Renderer* screen,
	double xPosText, double yPosText,
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
	isUnlock = true;
}

ButtonObject::~ButtonObject() {
	cleanUp();
}

InfoPlayer::InfoPlayer() {
	username = "";
	password = "";
	score = 0;
	yourHighScore = 0;
	level = 0;
	life = ORIGINAL_LIFE;
	for (int i = 0; i < MAX_LEVEL + FIX_ZERO_INDEX; ++i) unlockLevel[i] = 0;
}

InfoPlayer::~InfoPlayer() {

}