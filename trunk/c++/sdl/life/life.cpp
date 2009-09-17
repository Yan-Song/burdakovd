#include <iostream>

using namespace std;

#include "life.h"
#include "Vector.h"
#include <ctime>

LifeApplication::LifeApplication()
{
	lasttime = time(NULL);
	lastframes = 0;
	srand((unsigned int)time(NULL));
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Life", "");
	Populate();
}

void LifeApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();

		else if(sym == SDLK_r)
			Populate();
	}
}

void LifeApplication::Main()
{
	Turn();
	if(lasttime != time(NULL))
	{
		lasttime = time(NULL);
		cout<<"FPS: "<<(frames-lastframes)<<endl;
		lastframes = frames;
	}
}

void LifeApplication::Populate()
{
	for(int i=0; i<ScreenSize.y; ++i)
		for(int j=0; j<ScreenSize.x; ++j)
			map[0][i][j] = rand() % 100 < Density;
	current = 0;
}

void LifeApplication::Turn()
{
	int previous = current;
	current = 1 - current;

	for(int i=0; i<ScreenHeight; ++i)
		for(int j=0; j<ScreenWidth; ++j)
		{
			int neighbours = 0;
			for(int di=-1; di<=1; ++di)
				for(int dj=-1; dj<=1; ++dj)
					if(!(di==0 && dj==0))
					{
						int x = (j + dj + ScreenWidth) % ScreenWidth;
						int y = (i + di + ScreenHeight) % ScreenHeight;
						if(map[previous][y][x])
							++neighbours;
					}
			if(neighbours < minimumNeighbours || neighbours > maximumNeighbours)
				map[current][i][j] = false;
			else if(neighbours == neighboursForBaby)
				map[current][i][j] = true;
			else
				map[current][i][j] = map[previous][i][j];
		}
}

void LifeApplication::Render()
{
	LockSurface(Screen);
	for(int i=0; i<ScreenHeight; ++i)
		for(int j=0; j<ScreenWidth; ++j)
			if(map[current][i][j])
				DrawPixel(Screen, Point(j, i), alive);
			else
				DrawPixel(Screen, Point(j, i), dead);
	UnlockSurface(Screen);
	SDL_Flip(Screen);
}

const Color LifeApplication::alive = Color(255, 255, 0);
const Color LifeApplication::dead = Color(0, 0, 255);
const Point LifeApplication::ScreenSize = Point(LifeApplication::ScreenWidth, LifeApplication::ScreenHeight);
