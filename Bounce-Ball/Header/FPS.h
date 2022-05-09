#ifndef __FPS__
#define __FPS__
class FPS {
public:
	FPS();
	~FPS();
	void start();
	void stop();
	void paused();
	void unpaused();
	int getTicks();
	bool getIsStarted();
	bool getIsPaused();
private:
	int startTick;
	int pauseTick;
	bool isPaused;
	bool isStarted;
};
#endif
