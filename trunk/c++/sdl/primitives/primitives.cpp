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
#include "MyScene.h"
#include "Sprite.h"

class PineTree : public CompoundObject
{
public:
	PineTree(const Vector2D& center)
	{
		Center = center;		
		
		Add(new Triangle2D(Vector2DByCoords(15, 15), Vector2DByCoords(-15, 15), Vector2DByCoords(0, 0), Palette::Green));

		Add(new Triangle2D(Vector2DByCoords(10, 0), Vector2DByCoords(-10, 0), Vector2DByCoords(0, -10), Palette::Green));
	
		Add(new Triangle2D(Vector2DByCoords(5, -10), Vector2DByCoords(-5, -10), Vector2DByCoords(0, -15), Palette::Green));
	}
};

PrimitivesApplication::PrimitivesApplication() : scene(ScreenWidth, ScreenHeight)
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	lasttime = time(NULL);
		
	scene.Center = ScreenPointByCoords(ScreenWidth / 2, ScreenHeight / 2);
	
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
	
	scene.Rotate(0.01);
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
