#include "primitives.h"
#include "sdlapplication.h"
#include "Vector.h"
#include "color.h"
#include <cmath>
#include <ctime>
#include <cstring>
#include "line.h"
#include "matrix.h"
#include <iostream>

const Color yellow = Color(255, 255, 0);
const Color black = Color(0, 0, 0);
const Color white = Color(255, 255, 255);
const Color background = black;
const Color sand = Color(200, 200, 0);
const Color cyan = Color(0, 255, 255);
const double density = 1, activity = 0.001;

PrimitivesApplication::PrimitivesApplication()
{
	srand(static_cast<unsigned int>(time(NULL)));

	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	
}

void PrimitivesApplication::Main()
{
	
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


	LockSurface(Screen);

    Point start(20, 220);
    Point finish(Screen->w-20, Screen->h-20);
    Point center = Point((start.x + finish.x) / 2, (start.y + finish.y) / 2);

	if(frames == 0)
    {
        // lines
        for(double x=start.x; x<=finish.x; x += 1)
            Line(start, Point(x, finish.y), 0x000000, Color(x/800, finish.y/600, 0.0)).Draw(Screen);
        
        for(double y=start.y; y<=finish.y; y += 1)
            Line(start, Point(finish.x, y), 0x000000, Color(finish.x/800, y/600, 0.0)).Draw(Screen);

        Point p1(10, 10);
        Point p2(50, 50);
        Line l(p1, p2, yellow);

        for(int i=0; i<10; ++i)
        {
            l.Draw(Screen);
            l.Scale(Point(200, 10), 0.5, 0.5);
        }
    }


    // chaos
	for(int x=400; x<780; ++x)
		for(int y=20; y<200; ++y)
		{
			double sx = sin(sf*x*0.1-cf*y*0.1);
			double sy = sin(cf*x*0.1-sf*y*0.1);
			DrawPixel(Screen, Point(x, y), Color(norm(sx), norm(sy), norm(-1)));
		}

	UnlockSurface(Screen);
	SDL_Flip(Screen);
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
