#include "Timer.h"
#include "SDL.h"

Timer::Timer(void)
{
	Reset();
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
	return static_cast<double>(SDL_GetTicks() - startTicks) * 1e-3;
}