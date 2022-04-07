#ifndef __LEVELGAME__
#define __LEVELGAME__ 

class LevelGame {
public:
	LevelGame();
	~LevelGame();
	static void LoadLevelGame(const char* NameFileMap, SDL_Renderer* Screen, 
								SDL_Event Event, InfoPlayer *infoPlayer);
private:

};
#endif