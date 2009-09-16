#ifndef LINE_H
#define LINE_H

#include "graphobject.h"
#include "Vector.h"
#include <SDL.h>
#include "color.h"

class Line : GraphObject
{
public:
	Point A, B;
	Color colorA, colorB;

	Line(Point a, Point b): A(a), B(b), colorA(0xffffff), colorB(0xffffff) { }

	Line(Point a, Point b, Color c): A(a), B(b), colorA(c), colorB(c) { }

    Line(Point a, Point b, Color ca, Color cb): A(a), B(b), colorA(ca), colorB(cb) { }

	virtual void Draw(SDL_Surface* surface);
};

#endif
