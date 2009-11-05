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
#include "Geometry2D.h"

PrimitivesApplication::PrimitivesApplication() : scene(ScreenWidth, ScreenHeight)
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	lasttime = time(NULL);
		
	scene.Center = Vector00;
	
	std::vector<Segment2D*> segments;
	for(int i = 0; i < 10; ++i)
	{
		segments.push_back(new Segment2D(Vector2DByCoords(Rand(ScreenWidth), Rand(ScreenHeight)),
										Vector2DByCoords(Rand(ScreenWidth), Rand(ScreenHeight)),
										Palette::Gray));
		scene.Add(segments[i]);
	}
	
	for(int i = 0; i < segments.size(); ++i)
		for(int j = 0; j < i; ++j)
		{
			Segment2D* first = segments[i];
			Segment2D* second = segments[j];

			if(Geometry2D::hasIntersection(first->A, first->B, second->A, second->B))
				scene.Add(new Circle2D(Geometry2D::Intersection(first->A, first->B, second->A, second->B), 5, Palette::Yellow));
		}
}

void PrimitivesApplication::Main()
{
	if(lasttime != time(NULL)) // прошла секунда
	{
		lasttime = time(NULL);
		std::cout<<"Time: "<<GetTime()<<"; FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
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
