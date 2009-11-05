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
#include "Sprite.h"
#include "Scene.h"
#include "Geometry2D.h"
#include "Cube.h"

PrimitivesApplication::PrimitivesApplication() : ZRotationSpeed(0), XRotationSpeed(0), RotationAccelerating(2.0)
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	lasttime = time(NULL);
		
	scene.Add(new Cube(Vector000, 100));
}

void PrimitivesApplication::Main()
{
	if(lasttime != time(NULL)) // прошла секунда
	{
		lasttime = time(NULL);
		std::cout<<"Time: "<<GetTime()<<"; FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
	}

	if(KeyState[SDLK_RIGHT])
		ZRotationSpeed += RotationAccelerating * dt;

	if(KeyState[SDLK_LEFT])
		ZRotationSpeed -= RotationAccelerating * dt;

	if(KeyState[SDLK_UP])
		XRotationSpeed -= RotationAccelerating * dt;

	if(KeyState[SDLK_DOWN])
		XRotationSpeed += RotationAccelerating * dt;

	XRotationSpeed /= exp(dt);
	ZRotationSpeed /= exp(dt);

	scene.RotateZ(ZRotationSpeed * dt);
	scene.RotateX(XRotationSpeed * dt);
}

void PrimitivesApplication::InitialRender()
{
	ClearScreen();

	Flip();
}

void PrimitivesApplication::Render()
{
	ClearScreen();
	
	// центр сцены где-то посредине экрана, на глубине в 200 пикселей...
	scene.Draw(this, Vector3DByCoords(ScreenWidth / 2, 200, ScreenHeight / 2));

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
