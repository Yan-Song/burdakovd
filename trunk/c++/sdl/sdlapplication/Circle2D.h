#ifndef CIRCLE_H
#define CIRCLE_H

#include "GraphObject.h"
#include "SDLApplication.h"
#include "Color.h"

class Circle2D :
	public GraphObject2D
{
private:
	void circlePoints(const SDLApplication* app, const Vector2D& center, const int x, const int y, const Color& color) const;

public:
	double R;
	Color color;

	Circle2D(const double r, const Color& c = Palette::White) :
		R(r), color(c)
		{
		};

	inline Circle2D(const Vector2D& center, const double r, const Color& c = Palette::White) :
		R(r), color(c)
		{
			Center = center;
		};

	virtual void Draw(SDLApplication* const app, const Vector& base) const;

	virtual void Rotate(const double phi);

	virtual void Scale(const Vector2D& coefficients);

	virtual ~Circle2D(void) {};
};

#endif
