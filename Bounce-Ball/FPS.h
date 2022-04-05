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
	int get_ticks();
	bool is_started();
	bool is_paused();
private:
	int start_tick_;
	int pause_tick_;
	bool is_paused_;
	bool is_started_;
};
#endif
