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

void PrimitivesApplication::InitialRender()
{
	
}

void PrimitivesApplication::Render()
{
	// делаю всякие эксперименты тут а не в InitialRender, чтобы по FPS смотреть скорость работы
    Lock();

	ClearScreen(Palette::Black);

	// CG-8: Заливаем экран грдиентом справа нелево от чёрного к красному.

	for(int i = 0; i < Screen->w; ++i)
		for(int j = 0; j < 100; ++j)
			DrawPixel(i, j, Gradient(Palette::Red, Palette::Black, Screen->w - i, i));

	ScreenPoint a = ScreenPointByCoords(300, 300), b = ScreenPointByCoords(500, 300);

	for(int i = 0; i < Screen->w; ++i)
		for(int j = 100; j < Screen->h; ++j)
		{
			ScreenPoint current = ScreenPointByCoords(i, j);
			DrawPixel(current,
				Palette::Green * max(0, (150 - static_cast<int>(b.Distance(current)))) / 150 +
				Palette::Red * max(0, (150 - static_cast<int>(a.Distance(current)))) / 150
			);
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
