#include <iostream>

using namespace std;

#include "life.h"
#include "Vector.h"
#include <ctime>

LifeApplication::LifeApplication()
{
	lasttime = time(NULL);
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
	if(lasttime != time(NULL)) // прошла секунда
	{
		lasttime = time(NULL);
		std::cout<<"FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
	}
}

void LifeApplication::Populate()
{
	for(int i=0; i<ScreenWidth; ++i)
		for(int j=0; j<ScreenHeight; ++j)
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
	Lock();
	for(int i=0; i<ScreenHeight; ++i)
		for(int j=0; j<ScreenWidth; ++j)
			if(map[current][i][j])
				DrawPixel(j, i, alive);
			else
				DrawPixel(j, i, dead);
	Unlock();
	Flip();
}

const Color LifeApplication::alive = Color(0xffff00);
const Color LifeApplication::dead = Color(0x0000ff);