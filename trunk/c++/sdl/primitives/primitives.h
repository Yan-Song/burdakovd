#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "sdlapplication.h"
#include <vector>
#include "line.h"

using namespace std;

typedef double pFunction(double);

class PrimitivesApplication : public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT;
	long long lasttime, lastframes;

protected:
	virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);

public:
	PrimitivesApplication();

};

#endif
