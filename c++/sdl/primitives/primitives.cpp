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
#include "Surface.h"

double f(const double x, const double y)
{
	return x * x * x + x * y;
	// x * y - седло
	// x * x + y * y - какая-то штука (параболоид?)
	// sqrt(x * x + y * y) - конус
	// x * x - типа параболы но плоскость
}

PrimitivesApplication::PrimitivesApplication() : ZRotationSpeed(0), XRotationSpeed(0), RotationAccelerating(2.0)
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
	lasttime = time(NULL);
	
	// направление координат X - вправо, Y - вперёд сквозь экран, Z - вверх
	
	// наблюдатель примерно на расстоянии около 1200 пикселей от центра экрана, перпендикулярно его плоскости
	position = Vector3DByCoords(ScreenWidth / 2, -1200, ScreenHeight / 2);

	// центр сцены где-то посредине экрана, на глубине в 200 пикселей...
	scene.Center = Vector3DByCoords(ScreenWidth / 2, 200, ScreenHeight / 2);

	// График функции двух переменных (с самой функцией можно поэкспериментировать в начале файла)
	GraphObject3D* surface = new Surface(f, -2, -2, 2, 2, 0.2, 0.2, Palette::Green);

	// растянуть в 50 раз
	surface->Scale(Vector111 * 50);

	// добавляем график в сцену
	scene.Add(surface);

	// чтобы было красивее можно немного наклонить сцену
	scene.RotateX(0.3);
	scene.RotateZ(0.3);
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
	
	IProjector* projector = new Projection::PerspectiveProjector(position);
	scene.Draw(this, Vector000, projector);
	delete projector;

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
