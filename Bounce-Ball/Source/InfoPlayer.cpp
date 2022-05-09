#include "../Header/InfoPlayer.h"

InfoPlayer::InfoPlayer() {
	username = "";
	password = "";
	score = 0;
	yourHighScore = 0;
	level = 0;
	life = ORIGINAL_LIFE;
	for (int i = 0; i < MAX_LEVEL + FIX_ZERO_INDEX; ++i) unlockLevel[i] = false;
}

InfoPlayer::~InfoPlayer() {

}