#include "radar.h"
#include "SDLApplication.h"
#include "Segment.h"
#include <cstdlib>
#include <SDL.h>
#include "Color.h"

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
		Segment2D(c, a, Palette::Green).Draw(this, Vector00);

        for(int i=0; i<x; ++i)
			DrawPixel(Rand(Screen->w), Rand(Screen->h), Palette::Black);
    }

    Unlock();

    SDL_Flip(Screen);
}