#include "Timer.h"
#include "SDL.h"

Timer::Timer(void) : startTicks(SDL_GetTicks())
{
}

void Timer::Reset(void)
{
	startTicks = SDL_GetTicks();
}

Timer::~Timer(void)
{
}

double Timer::GetTime() const
{
	return static_cast<double>(SDL_GetTicks() - startTicks) * 0.001;
}

