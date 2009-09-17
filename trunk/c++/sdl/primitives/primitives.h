#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "sdlapplication.h"

typedef double pFunction(double);

class PrimitivesApplication : public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	int map[ScreenHeight][ScreenWidth];
	void move(Point a, Point b);
	void DrawGraph(pFunction& f, Point base, double scale, double dx, double start, double end) const;

protected:
	virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);

public:
	PrimitivesApplication();

};

#endif
