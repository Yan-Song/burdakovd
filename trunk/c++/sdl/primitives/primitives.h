#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "sdlapplication.h"

typedef double pFunction(double);

class PrimitivesApplication : public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;

protected:
	virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);

public:
	PrimitivesApplication();

};

#endif
