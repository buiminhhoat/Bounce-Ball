#include "FPS.h"
#include "CommonFunc.h"

FPS::FPS() {
	startTick = 0;
	pauseTick = 0;
	isPaused = false;
	isStarted = false;
}

FPS::~FPS() {

}

void FPS::start() {
	isStarted = true;
	isPaused = false;

	startTick = SDL_GetTicks();
}

void FPS::stop() {
	isPaused = false;
	isStarted = false;
}

void FPS::paused() {
	if (isStarted == true && isPaused == false) {
		isPaused = true;
		pauseTick = SDL_GetTicks() - startTick;
	}
}

void FPS::unpaused() {
	if (isPaused == true) {
		isPaused = false;
		startTick = SDL_GetTicks() - pauseTick;
		pauseTick = 0;
	}
}

int FPS::getTicks() {
	if (isStarted == true) {
		if (isPaused == true) {
			return pauseTick;
		}
		else {
			return SDL_GetTicks() - startTick;
		}
	}
	return 0;
}

bool FPS::getIsStarted() {
	return isStarted;
}

bool FPS::getIsPaused() {
	return isPaused;
}