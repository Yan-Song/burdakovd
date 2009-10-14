#ifndef TRAINGLE_H
#define TRIANGLE_H

#include "graphobject.h"
#include "sdlapplication.h"
#include "Vector.h"
#include "color.h"

class Triangle2D :
	public GraphObject2D
{
public:
	Vector2D A, B, C;
	Color color;

	Triangle2D(const Color& c) : color(c) {};

	Triangle2D(const Vector2D& a, const Vector2D& b, const Vector2D& c, const Color& co = Palette::White)
		: A(a), B(b), C(c), color(co)
	{};

	virtual void Draw(const SDLApplication* app) const;

	virtual void Shift(const Vector2D& v);

	virtual ~Triangle2D(void);
};

#endif
