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
    double lsf = norm(sin(0.001 * frames));
	double lcf = norm(cos(0.001 * frames));

	double sf = sin(0.01 * frames * lsf);
	double cf = cos(0.01 * frames * lcf);


	Lock();
   
    // chaos
	for(int x=400; x<780; ++x)
		for(int y=20; y<200; ++y)
		{
			double sx = sin(sf*x*0.1-cf*y*0.1);
			double sy = sin(cf*x*0.1-sf*y*0.1);
			DrawPixel(OldHomogeneousPoint2D(x, y), DoubleColor(255*norm(sx), 255*norm(sy), 255*norm(-1)));
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
