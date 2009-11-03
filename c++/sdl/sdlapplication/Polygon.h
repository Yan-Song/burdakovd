#ifndef POLYGON_H
#define POLYGON_H

#include "GraphObject.h"
#include "Vector.h"
#include "SDLApplication.h"
#include "Color.h"
#include <vector>

class Polygon :
	public GraphObject2D
{
public:
	typedef std::vector<Point2D> Points;

	Points points;
	Color color;
	bool Filled;

	Polygon(const Color& c = Palette::White, const bool filled = false) : color(c), Filled(filled)
	{
	};

	Polygon(const Points& v, const Color& c = Palette::White, const bool filled = false) : points(v), color(c), Filled(filled)
	{
	};

	virtual void Draw(const SDLApplication* app, const Vector& base) const;

	virtual void Scale(const Vector2D& coefficients);

	virtual void Rotate(const double phi);

	// добавить точку (относительно Center)
	void Add(const Point2D& p);

	void Clear();
};

#endif
