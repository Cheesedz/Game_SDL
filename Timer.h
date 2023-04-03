#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	void start();

	void stop();

	void paused();

	void unpaused();

	int get_ticks();

	bool isStarted();

	bool isPaused();

private:
	int start_tick;
	int paused_tick;

	bool is_paused;
	bool is_started;
};