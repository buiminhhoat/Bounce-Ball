#include "GameMap.h"
#include <fstream>

using namespace std;

void GameMap::LoadMap(const char* NameFileMap) {
	ifstream input(NameFileMap, std::ifstream::in);
	int N, M;
	input >> M >> N;
	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			input >> game_map_.block[i][j];
			int val = game_map_.block[i][j];
			if (val == START_POINT) {
				game_map_.start_x_player_ = j * TILE_SIZE;
				game_map_.start_y_player_ = i * TILE_SIZE;
			}
			if (val == GROUND_BLOCK) {
				if (j > game_map_.max_x_) game_map_.max_x_ = j;
				if (i > game_map_.max_y_) game_map_.max_y_ = i;
			}
		}
	}

	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

	game_map_.start_x_ = 0;
	game_map_.start_y_ = 0;

	game_map_.file_map = NameFileMap;
	input.close();
}

void GameMap::LoadIMGBlock(SDL_Renderer* Screen) {
	char file_IMG[100];
	FILE* f = NULL;
	type_block[GROUND_BLOCK].LoadImage("img//block//GROUND_BLOCK.png", Screen);
}

void GameMap::DrawMap(SDL_Renderer* Screen) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x_ / TILE_SIZE;
	x1 = (game_map_.start_x_ % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_y_ / TILE_SIZE;
	y1 = (game_map_.start_y_ % TILE_SIZE) * -1;

	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map_.block[map_y][map_x];
			if (val != THORN && val != DYN_THORN) {
				type_block[val].setRectPos(j, i);
				type_block[val].Render(Screen);
			}
			++map_x;
		}
		++map_y;
	}
}

void GameMap::FixMap() {
	for (int i = 0; i < game_map_.max_y_; i += TILE_SIZE) {
		for (int j = 0; j < game_map_.max_x_; j += TILE_SIZE) {
			int val = game_map_.block[i / TILE_SIZE][j / TILE_SIZE];
			if (val == GROUND_BLOCK) continue;
			game_map_.block[i / TILE_SIZE][j / TILE_SIZE] = 0;
		}
	}
}