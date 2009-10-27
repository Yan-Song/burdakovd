#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "SDLApplication.h"
#include <vector>
#include "Segment.h"
#include "Circle2D.h"
#include "GraphObject.h"
#include "Scene.h"

class PrimitivesApplication : public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;
	long long lasttime;
	
	void DoNavigation();
	
	// скорость в пикселях в секунду
	double vx, vy;
	double accelerating;
	double stopping;
	double reflectK;
	static const int R = 200;
	Scene scene;
	
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
