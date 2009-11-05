#ifndef POLYGON_H
#define POLYGON_H

#include "GraphObject.h"
#include "Vector.h"
#include "SDLApplication.h"
#include "Color.h"
#include <vector>

class Polygon2D :
	public GraphObject2D
{
public:
	typedef std::vector<Point2D> Points;

	Points points;
	Color color;
	bool Filled;

	Polygon2D(const Color& c = Palette::White, const bool filled = false) : color(c), Filled(filled)
	{
	};

	Polygon2D(const Points& v, const Color& c = Palette::White, const bool filled = false) : points(v), color(c), Filled(filled)
	{
	};

	virtual void Draw(const SDLApplication* app, const Vector& base) const;

	virtual void Scale(const Vector2D& coefficients);

	virtual void Rotate(const double phi);

	// добавить точку (относительно Center)
	void Add(const Point2D& p);

	void Clear();
};

class Polygon3D :
	public GraphObject3D
{
public:
	typedef std::vector<Point3D> Points;

	Points points;
	Color color;

	Polygon3D(const Color& c = Palette::White) : color(c)
	{
	};

	Polygon3D(const Points& v, const Color& c = Palette::White) : points(v), color(c)
	{
	};

	virtual void Scale(const Vector3D& coefficients);

	virtual void Draw(const SDLApplication* app, const Vector3D& base) const;

	virtual void Rotate(const int axe, const double phi);

	// добавить точку (относительно Center)
	void Add(const Point3D& p);
};

#endif
