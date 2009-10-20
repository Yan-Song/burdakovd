#include "primitives.h"
#include "sdlapplication.h"
#include "Vector.h"
#include "color.h"
#include <cmath>
#include <ctime>
#include <cstring>
#include "Segment.h"
#include "matrix.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "Circle2D.h"
#include "Triangle2D.h"
#include "Polygon.h"

PrimitivesApplication::PrimitivesApplication()
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	lasttime = time(NULL);
	// начальная скорость
	vx = 0;
	vy = 0;
	// ускорение 100 пикселей / сек^2
	accelerating = 100;
	// торможение: 10 пикс / секунду^2
	stopping = 10;
	// коэффициент упругости отражения от стен, 1 - абс. упруго, 0 - неупруго
	reflectK = 0.8;
	
	center = ScreenPointByCoords(ScreenWidth / 2, ScreenHeight / 2);
	Me.push_back(new Circle2D(center, R, Palette::Yellow));
	Me.push_back(new Triangle2D(center + Vector2DByCoords(0, 0.2*R), center + Vector2DByCoords(0.2*R * cos(-Pi/6), 0.2*R * sin(-Pi/6)),
		center + Vector2DByCoords(0.2*R * cos(7*Pi/6), 0.2*R * sin(7*Pi/6)), Palette::Green));

	Polygon* star = new Polygon(Palette::Red);

	star->Add(center + Vector2DByCoords(R * cos(-Pi / 2), R * sin(-Pi / 2)));
	star->Add(center + Vector2DByCoords(R * cos(-Pi / 2 + 4 * Pi / 5), R * sin(-Pi / 2 + 4 * Pi / 5)));
	star->Add(center + Vector2DByCoords(R * cos(-Pi / 2 + 8 * Pi / 5), R * sin(-Pi / 2 + 8 * Pi / 5)));
	star->Add(center + Vector2DByCoords(R * cos(-Pi / 2 + 2 * Pi / 5), R * sin(-Pi / 2 + 2 * Pi / 5)));
	star->Add(center + Vector2DByCoords(R * cos(-Pi / 2 + 6 * Pi / 5), R * sin(-Pi / 2 + 6 * Pi / 5)));

	Me.push_back(star);
}

void PrimitivesApplication::Main()
{
	
	if(lasttime != time(NULL)) // прошла секунда
	{
		lasttime = time(NULL);
		std::cout<<"Time: "<<GetTime()<<"; FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
	}
	
	DoNavigation();
	
	vx -= stopping * sgn(vx) * dt;
	vy -= stopping * sgn(vy) * dt;

	Vector2D dr = Vector2DByCoords(vx * dt, vy * dt);
	center += dr;
	
	// движение
	for(int i = 0; i < Me.size(); ++i)
		Me[i]->Shift(dr);
	
	if(center[0] < R)
	{
		center[0] = R;
		vx = abs(reflectK * vx);
	}
	
	if(center[1] < R)
	{
		center[1] = R;
		vy = abs(reflectK * vy);
	}
	
	if(center[0] > ScreenWidth - R)
	{
		center[0] = ScreenWidth - R;
		vx = -abs(reflectK * vx);
	}
	
	if(center[1] > ScreenHeight - R)
	{
		center[1] = ScreenHeight - R;
		vy = -abs(reflectK * vy);
	}
}

void PrimitivesApplication::DoNavigation()
{
	if(KeyState[SDLK_UP])
	{
		vy -= accelerating * dt;
	}

	if(KeyState[SDLK_DOWN])
	{
		vy += accelerating * dt;
	}

	if(KeyState[SDLK_LEFT])
	{
		vx -= accelerating * dt;
	}

	if(KeyState[SDLK_RIGHT])
	{
		vx += accelerating * dt;
	}
}

void PrimitivesApplication::InitialRender()
{
	Lock();
	
	ClearScreen(Palette::Black);
	
	Unlock();
	Flip();
}

void PrimitivesApplication::Render()
{
	Lock();
	
	ClearScreen(Palette::Black);
	for(int i = 0; i < Me.size(); ++i)
		Me[i]->Draw(this);
	
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

PrimitivesApplication::~PrimitivesApplication()
{
	for(int i = 0; i < Me.size(); ++i)
		delete Me[i];
}
