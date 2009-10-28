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
#include "Sprite.h"

class PineTree : public CompoundObject
{
public:
	PineTree(const Vector2D& center)
	{
		Add(new Triangle2D(center + Vector2DByCoords(15, 15), center + Vector2DByCoords(-15, 15), center + Vector2DByCoords(0, 0), Palette::Green));

		Add(new Triangle2D(center + Vector2DByCoords(10, 0), center + Vector2DByCoords(-10, 0), center + Vector2DByCoords(0, -10), Palette::Green));
	
		Add(new Triangle2D(center + Vector2DByCoords(5, -10), center + Vector2DByCoords(-5, -10), center + Vector2DByCoords(0, -15), Palette::Green));
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
	
	scene.Center = ScreenPointByCoords(ScreenWidth / 2, ScreenHeight / 2);
	
	scene.Add(new Circle2D(R, Palette::Yellow));
	
	int TreeR = 25;

	ScreenPoint dx = ScreenPointByCoords(TreeR * 2, 0);
	ScreenPoint dy = ScreenPointByCoords(0, TreeR * 2);

	for(int xx = static_cast<int>(-R / TreeR); xx < R / TreeR; ++xx)	
		for(int yy = static_cast<int>(-R / TreeR); yy < R / TreeR; ++yy)
		{
			Vector2D center = xx * dx + yy * dy;
			if(center.Length() + TreeR < R)
				scene.Add(new PineTree(center));
		}

	scene.Add(new Sprite("logo.bmp"));
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

	// движение
	scene.Move(dr);
	
	if(scene.Center[0] < R)
	{
		scene.Center[0] = R;
		vx = abs(reflectK * vx);
	}
	
	if(scene.Center[1] < R)
	{
		scene.Center[1] = R;
		vy = abs(reflectK * vy);
	}
	
	if(scene.Center[0] > ScreenWidth - R)
	{
		scene.Center[0] = ScreenWidth - R;
		vx = -abs(reflectK * vx);
	}
	
	if(scene.Center[1] > ScreenHeight - R)
	{
		scene.Center[1] = ScreenHeight - R;
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
	ClearScreen(Palette::Black);
	Flip();
}

void PrimitivesApplication::Render()
{
	ClearScreen(Palette::Black);
	
	scene.Draw(this, Vector00);
	
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
