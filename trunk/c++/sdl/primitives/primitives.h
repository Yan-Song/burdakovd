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
	time_t lasttime;

	Scene3D scene;
	CompoundObject3D* Objects;
	Vector3D LightPosition;

	double ZRotationSpeed, XRotationSpeed;
	double RotationAccelerating;

	PrimitivesApplication(const PrimitivesApplication& );
	PrimitivesApplication operator=(const PrimitivesApplication& );
	
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
