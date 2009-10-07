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

	c = ScreenPointByCoords(ScreenWidth / 2, ScreenHeight / 2); // center

    double p = 0.3; //  количество нечерных точек от 0 до 1

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

	Vector2D a = Vector2DByCoords(c[0] + r * cos(phi), c[1] + r * sin(phi));

    Lock();

    {
        Line(c, a, 0x00ff00).Draw(this); //green

        for(int i=0; i<x; ++i)
            DrawPixel(Rand(Screen->w), Rand(Screen->h), 0x000000); //black
    }

    Unlock();

    SDL_Flip(Screen);
}