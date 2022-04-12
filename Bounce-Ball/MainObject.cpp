#include "MainObject.h"
#include "BaseObject.h"

#define debug1(a) cout << #a << " = " << a << ";"
#define debug1l(a) cout << #a << " = " << a << ";" << '\n'
#define debug2(a, b) cout << #a << " = " << a << "; " << #b << " = " << b << "; "
#define debug2l(a, b) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << '\n'
#define debug3(a, b, c) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; "
#define debug3l(a, b, c) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << '\n'
#define debug4(a, b, c, d) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << #d << " = " << d << "; "
#define debug4l(a, b, c, d) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << #d << " = " << d << "; " << '\n'

using namespace std;

MainObject::MainObject() {
	frame = 0;
	xPos = 0;
	yPos = 0;
	xVal = 0;
	yVal = 0;
	widthFrame = 0;
	heightFrame = 0;
	status = -1;
	inputType.up = 0;
	inputType.down = 0;
	inputType.left = 0;
	inputType.right = 0;
	inputType.jump = 0;
	onGround = false;
	mapX = 0;
	mapY = 0;
	comeBackTime = 0;
	idCheckpoint = -1;
}

MainObject::~MainObject() {
	cleanUp();
}

bool MainObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret == true) {
		widthFrame = rect.w / TILE_LAYER;
		heightFrame = rect.h;
	}
	return ret;
}

void MainObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < TILE_LAYER; ++i) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;
		}
	}
}

void MainObject::showImage(SDL_Renderer* des) {
	if (inputType.left == 1 || inputType.right == 1) {
		++frame;
	}
	else {
		frame = 0;
	}

	if (frame >= TILE_LAYER) {
		frame = 0;
	}

	if (comeBackTime == 0) {
		rect.x = xPos - mapX;
		rect.y = yPos - mapY;

		SDL_Rect renderQuad = { rect.x, rect.y, widthFrame, heightFrame };

		SDL_RenderCopy(des, object, &frameClip[frame], &renderQuad);
	}
}

void MainObject::inputAction(SDL_Event events, SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
			case SDLK_RIGHT: {
				status = WALK_RIGHT;
				inputType.right = 1;
				inputType.left = 0;
			}
			break;
			case SDLK_LEFT: {
				status = WALK_LEFT;
				inputType.left = 1;
				inputType.right = 0;
			}
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
			case SDLK_RIGHT: {
				inputType.right = 0;
			}
			break;
			case SDLK_LEFT: {
				inputType.left = 0;
			}
			break;
		}
	}

	if (events.key.keysym.sym == SDLK_SPACE) {
		inputType.jump = 1;
	}
	//if (events.type == SDL_MOUSEBUTTONDOWN) {
	//	if (events.button.button == SDL_BUTTON_RIGHT) {
	//		inputType.jump = 1;
	//	}
	//}
}

void MainObject::doPlayer(Map &mapData) {
	if (comeBackTime == 0) {
		xVal = 0;
		yVal += GRAVITY_SPEED;
		if (yVal >= MAX_FALL_SPEED) {
			yVal = MAX_FALL_SPEED;
		}

		if (inputType.left == 1) {
			xVal -= PLAYER_SPEED;
		}
		else if (inputType.right == 1) {
			xVal += PLAYER_SPEED;
		}

		if (inputType.jump == 1) {
			if (onGround == true) {
				yVal = -PLAYER_JUMP;
			}
			onGround = false;
			inputType.jump = 0;
		}
		checkPlayerVsMap(mapData);
		centerEntityOnMap(mapData);
	}

	if (comeBackTime > 0) {
		--comeBackTime;
		if (comeBackTime == 0) {
			onGround = false;
			if (xPos > DRAW_BACK) {
				xPos -= DRAW_BACK; // 4 tiles
				mapX -= DRAW_BACK;
			}
			else {
				xPos = 0;
			}
			yPos = 0;
			xVal = 0;
			yVal = 0;
		}
	}
}

void MainObject::centerEntityOnMap(Map &mapData) {
	mapData.startX = xPos - (SCREEN_WIDTH / 2);
	if (mapData.startX < 0) {
		mapData.startX = 0;
	}
	else if (mapData.startX + SCREEN_WIDTH >= mapData.maxX) {
		mapData.startX = mapData.maxX - SCREEN_WIDTH;
	}

	mapData.startY = yPos - (SCREEN_HEIGHT / 2);
	if (mapData.startY < 0) {
		mapData.startY = 0;
	}
	else if (mapData.startY + SCREEN_HEIGHT >= mapData.maxY) {
		mapData.startY = mapData.maxY - SCREEN_HEIGHT;
	}
}

void MainObject::checkPlayerVsMap(Map& mapData) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	
	int height_min = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;

	x1 = (xPos + xVal) / TILE_SIZE;
	x2 = (xPos + xVal + widthFrame) / TILE_SIZE;

	y1 = (yPos) / TILE_SIZE;
	y2 = (yPos + heightFrame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (xVal > 0) {
			if (mapData.block[y1][x2] != BLANK_TILES || mapData.block[y2][x2] != BLANK_TILES) {
				xPos = x2 * TILE_SIZE;
				xPos -= widthFrame;
				xVal = 0;
			}
		}
		else if (xVal < 0) {
			if (mapData.block[y1][x1] != BLANK_TILES || mapData.block[y2][x1] != BLANK_TILES) {
				xPos = (x1 + 1) * TILE_SIZE;
				xVal = 0;
			}
		}
	}
	else {
		xVal = 0;
	}

	// Check vertical
	int width_min = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
	x1 = xPos / TILE_SIZE;
	x2 = (xPos + width_min) / TILE_SIZE;

	y1 = (yPos + yVal) / TILE_SIZE;
	y2 = (yPos + yVal + heightFrame) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		float height_block1 = (x1 + 1) * TILE_SIZE - xPos;
		float height_block2 = heightFrame - height_block1;
		int select_block = 0;
		if (select_block == 0 && mapData.block[y2][x1] != BLANK_TILES) {
			if (height_block1 >= (1 - EQUILIBRIUM_RATIO) * widthFrame)
				select_block = 1;
		}
		if (select_block == 0 && mapData.block[y2][x2] != BLANK_TILES) {
			if (height_block2 >= (1 - EQUILIBRIUM_RATIO) * widthFrame)
				select_block = 2;
		}
		if (select_block == 0) {
			if (height_block1 > height_block2)
				select_block = 1;
			else
				select_block = 2;
		}

		if (yVal > 0) {
			if (height_block1 == TILE_SIZE) {
				if (mapData.block[y2][x1] != BLANK_TILES) {
					yPos = y2 * TILE_SIZE;
					yPos -= heightFrame;
					yVal = 0;
					onGround = true;
				}
			}
			else if (height_block2 == TILE_SIZE) {
				if (mapData.block[y2][x2] != BLANK_TILES) {
					yPos = y2 * TILE_SIZE;
					yPos -= heightFrame;
					yVal = 0;
					onGround = true;
				}
			}
			else if (mapData.block[y2][x1] != BLANK_TILES) {
				yPos = y2 * TILE_SIZE;
				yPos -= heightFrame;
				yVal = 0;
				onGround = true;
				if (height_block1 <= (1 - EQUILIBRIUM_RATIO) * widthFrame
					&& mapData.block[y2][x2] == BLANK_TILES)
					if (height_block1 <= FREE_ROLLING_SPEED)
						xPos += height_block1;
					else
						xPos += FREE_ROLLING_SPEED;
			}
			else if (mapData.block[y2][x2] != BLANK_TILES) {
				yPos = y2 * TILE_SIZE;
				yPos -= heightFrame;
				yVal = 0;
				onGround = true;
				if (height_block2 <= (1 - EQUILIBRIUM_RATIO) * widthFrame
					&& mapData.block[y2][x1] == BLANK_TILES)
					if (height_block2 <= FREE_ROLLING_SPEED)
						xPos -= height_block2;
					else
						xPos -= FREE_ROLLING_SPEED;
			}
		}
		else if (yVal < 0) {
			if (height_block1 == TILE_SIZE) {
				if (mapData.block[y1][x1] != BLANK_TILES) {
					yPos = (y1 + 1) * TILE_SIZE;
					yVal = 0;
				}
			}
			else if (height_block2 == TILE_SIZE) {
				if (mapData.block[y1][x2] != BLANK_TILES) {
					yPos = (y1 + 1) * TILE_SIZE;
					yVal = 0;
				}
			}
			else if (mapData.block[y1][x1] != BLANK_TILES) {
				yPos = (y1 + 1) * TILE_SIZE;
				if (height_block1 <= (1 - EQUILIBRIUM_RATIO) * widthFrame
					&& mapData.block[y1][x2] == BLANK_TILES)
					if (height_block1 <= FREE_ROLLING_SPEED)
						xPos += height_block1;
					else
						xPos += FREE_ROLLING_SPEED;
				yVal = 0;
			}
			else if (mapData.block[y1][x2] != BLANK_TILES) {
				yPos = (y1 + 1) * TILE_SIZE;
				if (height_block2 <= (1 - EQUILIBRIUM_RATIO) * widthFrame
					&& mapData.block[y1][x1] == BLANK_TILES)
					if (height_block2 <= FREE_ROLLING_SPEED)
						xPos -= height_block2;
					else
						xPos -= FREE_ROLLING_SPEED;
				yVal = 0;
			}
		}
	}

	xPos += xVal;
	yPos += yVal;

	if (xPos < 0) {
		xPos = 0;
	}
	else if (xPos + widthFrame > mapData.maxX) {
		xPos = mapData.maxX - widthFrame;
	}

	if (yPos < 0) {
		yPos = 0;
	}
	if (yPos > mapData.maxY) {
		comeBackTime = 10;
	}
}