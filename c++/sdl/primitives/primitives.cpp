#include "primitives.h"
#include "SDLApplication.h"
#include "Vector.h"
#include "Color.h"
#include <cmath>
#include <ctime>
#include <cstring>
#include "Segment.h"
#include "Matrix.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "Circle2D.h"
#include "Triangle2D.h"
#include "Polygon.h"
#include "CompoundObject.h"
#include "Scene.h"

class PineTree : public CompoundObject
{
public:
	PineTree(const Vector2D& center)
	{
		Add(new Triangle2D(center + Vector2DByCoords(15, 0), center + Vector2DByCoords(-15, 0), center + Vector2DByCoords(0, -15), Palette::Green));

		Add(new Triangle2D(center + Vector2DByCoords(10, -15), center + Vector2DByCoords(-10, -15), center + Vector2DByCoords(0, -25), Palette::Green));
	
		Add(new Triangle2D(center + Vector2DByCoords(5, -25), center + Vector2DByCoords(-5, -25), center + Vector2DByCoords(0, -30), Palette::Green));
	}
};

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
	
	scene.Add(new Circle2D(center, R, Palette::Yellow));
	
	ScreenPoint dx = ScreenPointByCoords(60, 0);

	for(int i = -3; i < 4; ++i)	
		scene.Add(new PineTree(center + i * dx));
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
	scene.Move(dr);
	
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
	
	scene.Draw(this, Vector2D());
	
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
	
}
