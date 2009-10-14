#ifndef LINE_H
#define LINE_H

#include "graphobject.h"
#include "Vector.h"
#include <SDL.h>
#include "color.h"
#include "matrix.h"

class Segment2D : public GraphObject2D
{
public:
	Point2D A, B;
	Color color;

	Segment2D(Point2D a, Point2D b): A(a), B(b), color(0xffffff) { }

	Segment2D(Point2D a, Point2D b, Color c): A(a), B(b), color(c) { }

	virtual void Draw(const SDLApplication*) const;

	virtual void Shift(const Vector2D& v);
 
    virtual ~Segment2D() {};
};

#endif
