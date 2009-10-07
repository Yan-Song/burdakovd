#include "primitives.h"
#include "sdlapplication.h"
#include "Vector.h"
#include "color.h"
#include <cmath>
#include <ctime>
#include <cstring>
#include "line.h"
#include "matrix.h"
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

const Color yellow = Color(255, 255, 0);
const Color black = Color(0, 0, 0);
const Color white = Color(255, 255, 255);
const Color background = black;
const Color sand = Color(200, 200, 0);
const Color cyan = Color(0, 255, 255);
const double density = 1, activity = 0.001;

PrimitivesApplication::PrimitivesApplication()
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	lasttime = time(NULL);
	lastframes = 0;
}

void PrimitivesApplication::Main()
{
	if(lasttime != time(NULL))
	{
		lasttime = time(NULL);
		cout<<"FPS: "<<(frames-lastframes)<<endl;
		lastframes = frames;
	}
}

double norm(double x)
{
	return 0.5 * (1.0 + x);
}

template<class T>
int sgn(T x)
{
	return x<0 ? -1 :
		(x>0 ? 1 : 0);
}

void PrimitivesApplication::Render()
{
    Lock();

	// CG-6: Заливаем весь экран красным, синим, зелёным цветами.

	// левый верхний угол - красный
	for(int i = 0; i < Screen->w / 2; ++i)
		for(int j = 0; j < Screen->h / 2; ++j)
			DrawPixel(i, j, Palette::Red);

	// правый верхний угол - зелёный
	for(int i = Screen->w / 2; i < Screen->w; ++i)
		for(int j = 0; j < Screen->h / 2; ++j)
			DrawPixel(i, j, Palette::Green);

	// левый нижний угол - синий
	for(int i = 0; i < Screen->w / 2; ++i)
		for(int j = Screen->h / 2; j < Screen->h; ++j)
			DrawPixel(i, j, Palette::Blue);

	// правый нижний - все сразу
	for(int i = Screen->w / 2; i < Screen->w; ++i)
		for(int j = Screen->h / 2; j < Screen->h; ++j)
		{
			Color color;

			int c = Rand(1, 3);

			if(c == 1)
				color = Palette::Red;
			else if (c == 2)
				color = Palette::Green;
			else
				color = Palette::Blue;

			DrawPixel(i, j, color);
				
		}

	Unlock();
	Flip();
}

void PrimitivesApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();
	}
}
