#include "primitives.h"
#include "sdlapplication.h"
#include "Vector.h"
#include "color.h"
#include <cmath>
#include <ctime>
#include <cstring>
#include "line.h"

const Point PrimitivesApplication::ScreenSize = Point(PrimitivesApplication::ScreenWidth, PrimitivesApplication::ScreenHeight);
const Color yellow = Color(255, 255, 0);
const Color black = Color(0, 0, 0);
const Color white = Color(255, 255, 255);
const Color background = black;
const Color sand = Color(200, 200, 0);
const Color cyan = Color(0, 255, 255);
const double density = 1, activity = 0.001;

PrimitivesApplication::PrimitivesApplication()
{
	srand(time(NULL));

	InitializeSDL(ScreenSize, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);

	memset(map, 0, sizeof(map));
	
}

void PrimitivesApplication::Main()
{
	
}

void PrimitivesApplication::DrawGraph(pFunction& f, Point base, double scale, double dx, double start, double end) const
{
	for(double fx = start; fx < end; fx += dx)
	{
		double fy = -f(fx);
		DrawPixel(Screen, Point(base, fx, fy, scale), yellow);
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


	LockSurface(Screen);

    Point start(20, 220);
    Point finish(Screen->w-20, Screen->h-20);
    Point center = (start + finish) / 2;

	if(frames == 0)
    {

        // pixels
	    DrawGraph(sin, Point(20, 50), 10, 1.0, 0, 36);
	    DrawGraph(sin, Point(20, 80), 10, 0.5, 0, 36);
	    DrawGraph(sin, Point(20, 110), 10, 0.2, 0, 36);
	    DrawGraph(sin, Point(20, 140), 10, 0.1, 0, 36);
	    DrawGraph(sin, Point(20, 170), 10, 0.05, 0, 36);

        

	    
        // lines
        for(int x=start.x; x<=finish.x; x += 1)
            Line(start, Point(x, finish.y), 0x000000, Color(x*255/800, finish.y*255/600, 0)).Draw(Screen);
        
        for(int y=start.y; y<=finish.y; y += 1)
            Line(start, Point(finish.x, y), 0x000000, Color(finish.x*255/800, y*255/600, 0)).Draw(Screen);
        
    }


    // chaos
	for(int x=400; x<780; ++x)
		for(int y=20; y<200; ++y)
		{
			double sx = sin(sf*x*0.1-cf*y*0.1);
			double sy = sin(cf*x*0.1-sf*y*0.1);
			DrawPixel(Screen, Point(x, y), Color(norm(sx), norm(sy), norm(1)));
		}

	UnlockSurface(Screen);
	SDL_Flip(Screen);
}

void PrimitivesApplication::move(Point a, Point b)
{
	if(map[a.y][a.x] == sand && b.y < Screen->h && b.x < Screen->w && b.x >= 0 && b.y >= 0) 
		if(map[b.y][b.x] == background)
		{
			map[a.y][a.x] = background;
			map[b.y][b.x] = sand;

			DrawPixel(Screen, Point(a.x,a.y), background);
			DrawPixel(Screen, Point(b.x,b.y), sand);
		}
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
