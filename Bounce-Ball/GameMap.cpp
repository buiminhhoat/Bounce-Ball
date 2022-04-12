#include "GameMap.h"
#include <fstream>

using namespace std;

void GameMap::loadMap(const char* nameFileMap) {
	ifstream input(nameFileMap, std::ifstream::in);
	int N, M;
	input >> M >> N;
	gameMap.maxX = 0;
	gameMap.maxY = 0;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			input >> gameMap.block[i][j];
			int val = gameMap.block[i][j];
			if (val == START_POINT) {
				gameMap.startXPlayer = j * TILE_SIZE;
				gameMap.startYPlayer = i * TILE_SIZE;
			}
			if (val == GROUND_BLOCK) {
				if (j > gameMap.maxX) gameMap.maxX = j;
				if (i > gameMap.maxY) gameMap.maxY = i;
			}
		}
	}

	gameMap.maxX = (gameMap.maxX + 1) * TILE_SIZE;
	gameMap.maxY = (gameMap.maxY + 1) * TILE_SIZE;

	gameMap.startX = 0;
	gameMap.startY = 0;

	gameMap.fileMap = nameFileMap;
	input.close();
}

void GameMap::loadIMGBlock(SDL_Renderer* screen) {
	char file_IMG[100];
	FILE* f = NULL;
	type_block[GROUND_BLOCK].loadImage("img//block//GROUND_BLOCK.png", screen);
}

void GameMap::drawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = gameMap.startX / TILE_SIZE;
	x1 = (gameMap.startX % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = gameMap.startY / TILE_SIZE;
	y1 = (gameMap.startY % TILE_SIZE) * -1;

	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = gameMap.startX / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = gameMap.block[map_y][map_x];
			if (val != THORN && val != DYN_THORN) {
				type_block[val].setRectPos(j, i);
				type_block[val].render(screen);
			}
			++map_x;
		}
		++map_y;
	}
}

void GameMap::fixMap() {
	for (int i = 0; i < gameMap.maxY; i += TILE_SIZE) {
		for (int j = 0; j < gameMap.maxX; j += TILE_SIZE) {
			int val = gameMap.block[i / TILE_SIZE][j / TILE_SIZE];
			if (val == GROUND_BLOCK) continue;
			gameMap.block[i / TILE_SIZE][j / TILE_SIZE] = 0;
		}
	}
}