#include <iostream>

using namespace std;

#include "WormsApplication.h"
#include "Vector.h"
#include <ctime>

WormsApplication::WormsApplication()
{
	lasttime = time(NULL);
	lastframes = 0;
	srand((unsigned int)time(NULL));
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Worms", "");
}

void WormsApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();
	}
}

void WormsApplication::Main()
{
    LockSurface(Screen);
	// ...
	UnlockSurface(Screen);
	SDL_Flip(Screen);

	if(lasttime != time(NULL))
	{
		lasttime = time(NULL);
		cout<<"FPS: "<<(frames-lastframes)<<endl;
		lastframes = frames;
	}
}

void WormsApplication::Render()
{
    /*
    LockSurface(Screen);
	// ...
	UnlockSurface(Screen);
	SDL_Flip(Screen);
    */
}

const Point WormsApplication::ScreenSize = Point(WormsApplication::ScreenWidth, WormsApplication::ScreenHeight);
