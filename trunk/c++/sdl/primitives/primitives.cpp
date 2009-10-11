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

PrimitivesApplication::PrimitivesApplication()
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	lasttime = time(NULL);
	// начальное положение
	Position = Vector2DByCoords(ScreenWidth / 2, ScreenHeight / 2);
	// начальная скорость
	vx = 0;
	vy = 0;
	// ускорение 100 пикселей / сек^2
	accelerating = 100;
	// торможение: 10 пикс / секунду^2
	stopping = 10;
	// коэффициент упругости отражения от стен, 1 - абс. упруго, 0 - неупруго
	reflectK = 0.8;
}

void PrimitivesApplication::Main()
{
	
	if(lasttime != time(NULL)) // прошла секунда
	{
		lasttime = time(NULL);
		std::cout<<"FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
	}
	
	OldPosition = Position;
	DoNavigation();
	
	vx -= stopping * sgn(vx) * dt;
	vy -= stopping * sgn(vy) * dt;

	Position[0] += vx * dt;
	Position[1] += vy * dt;
	
	if(Position[0] < 0)
	{
		Position[0] = 0;
		vx = abs(reflectK * vx);
	}
	
	if(Position[1] < 0)
	{
		Position[1] = 0;
		vy = abs(reflectK * vy);
	}
	
	if(Position[0] > ScreenWidth)
	{
		Position[0] = ScreenWidth;
		vx = -abs(reflectK * vx);
	}
	
	if(Position[1] > ScreenHeight)
	{
		Position[1] = ScreenHeight;
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
	
	Line(OldPosition, Position, 0x505050).Draw(this);
	DrawPixel(Position, Palette::Yellow);
	
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
