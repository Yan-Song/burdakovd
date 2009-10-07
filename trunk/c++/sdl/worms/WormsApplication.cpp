#include <iostream>

using namespace std;

#include "WormsApplication.h"
#include "Vector.h"
#include <ctime>


WormsApplication::WormsApplication()
{
	lasttime = time(NULL);
	lastframes = 0;
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
    Lock();
	// ...
	Unlock();
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
    Lock(Screen);
	// ...
	Unlock(Screen);
	SDL_Flip(Screen);
    */
}

