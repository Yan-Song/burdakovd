#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "SDLApplication.h"
#include <vector>
#include "Segment.h"
#include "Circle2D.h"
#include "GraphObject.h"
#include "CompoundObject.h"
#include "Scene.h"

// направление координат X - вправо, Y - вперёд сквозь экран, Z - вверх

class PrimitivesApplication : public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;
	long long lasttime;
	Scene3D scene;
	CompoundObject3D* Objects;
	double ZRotationSpeed, XRotationSpeed;
	double RotationAccelerating;
	Vector3D LightPosition;
	
protected:
	virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);

	virtual void InitialRender();

public:
	PrimitivesApplication();

	virtual ~PrimitivesApplication();
	
};

#endif
