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
#include "Projection.h"
#include "Triangle3D.h"
#include "Frustum.h"
#include "Pencil.h"
#include "DemoScene.h"

namespace
{
	const int ScreenWidth = 800;
	const int ScreenHeight = 600;
	const int ColorDepth = 0;
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;
}

PrimitivesApplication::PrimitivesApplication() :
	// наблюдатель примерно на расстоянии около 1200 пикселей от центра экрана, перпендикулярно его плоскости
	scene(Vector3DByCoords(ScreenWidth / 2, -1200, ScreenHeight / 2), \
		ScreenPointByCoords(ScreenWidth, ScreenHeight), this),
	Objects(new CompoundObject3D()),
	LightPosition(Vector3DByCoords(20000, -10000, 10000)),
	statsTimer(),
	ZRotationSpeed(0.0), XRotationSpeed(0.0), RotationAccelerating(2.0)	
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);

	// создаём некоторый набор объектов и добавляем его в сцену
	scene.Add(Objects);

	// центр где-то посредине экрана, на глубине в 400 пикселей...
	Objects->Center = Vector3DByCoords(ScreenWidth / 2, 400, ScreenHeight / 2);

	// добавляем демо-сцену в набор
	Objects->Add(new DemoScene(Vector000));
	
	// чтобы было красивее можно немного наклонить набор
	Objects->RotateX(1.0);
	Objects->RotateZ(0.2);
	Objects->RotateY(-0.1);

	// добавить освещенность
	scene.AddLight(LightPosition, 1);

	statsTimer.Start();
}

void PrimitivesApplication::Main()
{
	if(statsTimer.Elapsed(1000)) // прошла секунда
	{
		statsTimer.Start();
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

	Objects->RotateZ(ZRotationSpeed * dt);
	Objects->RotateX(XRotationSpeed * dt);
}

void PrimitivesApplication::InitialRender()
{
	ClearScreen();

	Flip();
}

void PrimitivesApplication::Render()
{
	scene.Render();
}

void PrimitivesApplication::ProcessEvent(const SDL_Event& Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();

		if(sym == SDLK_l)
		{
			if(scene.LightCount() == 0)
				scene.AddLight(LightPosition, 1);
			else
				scene.ClearLights();
		}

		if(sym == SDLK_s)
		{
			scene.Smoothing = !scene.Smoothing;
		}
	}
}

PrimitivesApplication::~PrimitivesApplication()
{
	
}
