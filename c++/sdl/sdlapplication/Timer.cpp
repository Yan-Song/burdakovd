#include <SDL.h>
#include "Timer.h"
#include "Utils.h"

Timer::Timer(void) : ticks(), started(false), paused(false)
{
}

void Timer::Start()
{
	ticks = SDL_GetTicks();
	started = true;
	paused = false;
}

void Timer::Stop()
{
	started = paused = false;
}

void Timer::Pause()
{
	assert(started);

	// запоминаем текущее значение таймера
	ticks = GetTicks();
	paused = true;
}

void Timer::Resume()
{
	assert(started);
	
	if(paused)
	{
		Uint32 cticks = SDL_GetTicks();
		assert(cticks >= ticks);

		ticks = cticks - ticks;

		paused = false;
	}
}

Uint32 Timer::GetTicks() const
{
	assert(started);

	if(paused)
	{
		return ticks;
	}
	else
	{
		Uint32 cticks = SDL_GetTicks();

		assert(cticks >= ticks);

		return cticks - ticks;
	}
}

double Timer::GetTime() const
{
	return static_cast<double>(GetTicks()) * 0.001;
}

Timer::~Timer(void)
{

}
