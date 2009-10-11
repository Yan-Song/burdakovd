#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "sdlapplication.h"
#include <vector>
#include "line.h"

class PrimitivesApplication : public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_SWSURFACE;
	long long lasttime;
	
	void DoNavigation();
	
	Point2D Position, OldPosition;
	// скорость в пикселях в секунду
	double vx, vy;
	double accelerating;
	double stopping;
	double reflectK;

protected:
	virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);

	virtual void InitialRender();

public:
	PrimitivesApplication();
	
};

#endif
