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

	Segment2D(Point2D a, Point2D b, Color c = Palette::White): A(a), B(b), color(c) { }

	virtual void Draw(const SDLApplication*, const Vector& base) const;

    virtual ~Segment2D() {};
};

#endif
