#ifndef XL_TIMER_HPP
#define XL_TIMER_HPP

#include <SDL.h>

//rewrite to use std::chrono

namespace XL
{
class Timer
{
	public:
		Timer();

		void start();
		void stop();
		void pause();
		void unpause();
		void restart();

		Uint32 getTicks();

		bool isStarted();
		bool isPaused();

	private:
		//clock time when timer started
		Uint32 startTicks;
		//ticks stored when timer was paused
		Uint32 pausedTicks;

		bool paused;
		bool started;
};
};

#endif