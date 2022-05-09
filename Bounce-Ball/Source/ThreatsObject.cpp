#include "../Header/ThreatsObject.h"

ThreatsObject::ThreatsObject() {
	onGround = false;
	animationA = 0;
	animationB = 0;
	inputType.left = false;
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
	int widthMin = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
	x1 = xPos / TILE_SIZE;
	x2 = (xPos + widthMin) / TILE_SIZE;

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
		}
		else if (yPos < animationA) {
			inputType.up = false;
			inputType.down = true;
		}
	}
}
