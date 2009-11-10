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

	Segment2D(const Point2D& a, const Point2D& b, const Color& c = Palette::White): A(a), B(b), color(c) { }

	virtual void Draw(SDLApplication* const, const Vector& base) const;

	virtual void Rotate(const double phi);

	virtual void Scale(const Vector2D& coefficients);

    virtual ~Segment2D() {};
};

#endif
