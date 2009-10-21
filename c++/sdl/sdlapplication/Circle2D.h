#ifndef CIRCLE_H
#define CIRCLE_H

#include "GraphObject.h"
#include "SDLApplication.h"
#include "Color.h"

class Circle2D :
	public GraphObject2D
{
private:
	void circlePoints(const SDLApplication* app, const int x, const int y, const Color& color) const;

public:
	Vector2D Center;
	double R;
	Color color;

	Circle2D(void) {};

	Circle2D(const Vector2D& v, const double r) :
		Center(v), R(r), color(Palette::White)
		{
		};

	Circle2D(const Vector2D& v, const double r, const Color& c) :
		Center(v), R(r), color(c)
		{
		};

	virtual void Draw(const SDLApplication* app) const;

	virtual void Shift(const Vector2D& v);

	virtual ~Circle2D(void) {};
};

#endif
