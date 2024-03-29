#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Color.h"
#include "CompoundObject.h"
#include "GraphObject.h"
#include "SDLApplication.h"
#include "Vector.h"

class Polygon2D :
	public GraphObject2D
{
private:
	class PixelDrawer;
	class PointsTransformer;

public:
	typedef std::vector<Point2D> Points;

	Points points;
	Color color;
	bool Filled;

	Polygon2D(const Color& c = Palette::White, const bool filled = false) : points(), color(c), Filled(filled)
	{
	};

	Polygon2D(const Points& v, const Color& c = Palette::White, const bool filled = false) :
		points(v), color(c), Filled(filled)
	{
	};

	virtual void Draw(SDLApplication* const app, const Vector& base) const;

	virtual void Scale(const Vector2D& coefficients);

	virtual void Rotate(const double phi);

	// добавить точку (относительно Center)
	void Add(const Point2D& p);

	void Clear();
};

class Polygon3D :
	public CompoundObject3D
{
private:
	Point3D first, last;
	unsigned int vcount;

public:
	Color color;

	Polygon3D(const Color& _color = Palette::White) : first(false), last(false), vcount(0), color(_color)
	{
	};

	// добавить точку (относительно Center)
	void Add(const Point3D& p);
};

#endif
