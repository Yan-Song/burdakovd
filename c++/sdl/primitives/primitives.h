#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include <Circle2D.h>
#include <CompoundObject.h>
#include <GraphObject.h>
#include <Scene.h>
#include <SDLApplication.h>
#include <Segment.h>
#include <Timer.h>

// направление координат X - вправо, Y - вперёд сквозь экран, Z - вверх

class PrimitivesApplication : public SDLApplication
{
private:
	Scene3D scene;
	CompoundObject3D* Objects;
	Vector3D LightPosition;

	Timer statsTimer;

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
