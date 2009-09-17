#include "radar.h"
#include "sdlapplication.h"
#include "line.h"
#include <cstdlib>
#include <SDL.h>

Radar::Radar()
{
    InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);

    r = 0.45 * min(Screen->w, Screen->h);

    phi = 0;
    dphi = 0.001;

    c = Point(ScreenWidth, ScreenHeight) / 2;

    double p = 0.5;

    x = static_cast<int>(Screen->w * Screen->h * dphi * (1 - p) / (2 * Pi * p));
}

void Radar::ProcessEvent(SDL_Event Event)
{
    if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();
	}
}

void Radar::Main()
{

}

void Radar::Render()
{
    phi += dphi;

    Point a(c.x/c.k + r * cos(phi), c.y/c.k + r * sin(phi));

    LockSurface(Screen);

    {
        Line(c, a, 0x008000, 0x00ff00).Draw(Screen);

        for(int i=0; i<x; ++i)
            DrawPixel(Screen, Rand(Screen->w), Rand(Screen->h), 0x000000);
    }

    UnlockSurface(Screen);

    SDL_Flip(Screen);
}