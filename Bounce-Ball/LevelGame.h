#ifndef __LEVELGAME__
#define __LEVELGAME__ 

class LevelGame {
public:
	LevelGame();
	~LevelGame();
	int loadLevelGame(const char* nameFileMap, SDL_Renderer* screen, 
								SDL_Event event, InfoPlayer *infoPlayer);
private:

};
#endif