#include "Timer.h"
#include "SDL.h"

Timer::Timer(void)
{
	startTicks = SDL_GetTicks();
}

Timer::~Timer(void)
{

}

double Timer::GetTime() const
{
	return (SDL_GetTicks() - startTicks) * 1e-3;
}