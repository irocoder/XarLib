#include "Timer.hpp"

XL::Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void XL::Timer::start()
{
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void XL::Timer::stop()
{
	started = false;
	paused = false;

	startTicks = 0;
	pausedTicks = 0;
}

void XL::Timer::restart()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;

	started = true;
}

void XL::Timer::pause()
{
	if(started && !paused)
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void XL::Timer::unpause()
{
	if(started && paused)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 XL::Timer::getTicks()
{
	Uint32 time = 0;

	if(started)
	{
		if(paused)
		{
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool XL::Timer::isStarted()
{
	return started;
}

bool XL::Timer::isPaused()
{
	return paused && started;
}