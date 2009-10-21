#ifndef LINE_H
#define LINE_H

#include "GraphObject.h"
#include "Vector.h"
#include <SDL.h>
#include "Color.h"
#include "Matrix.h"

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
