#ifndef POLYGON_H
#define POLYGON_H

#include "graphobject.h"
#include "Vector.h"
#include "sdlapplication.h"
#include "color.h"
#include <vector>

class Polygon :
	public GraphObject2D
{
public:
	typedef std::vector<Point2D> Points;

	Points points;
	Color color;

	Polygon(const Color& c = Palette::White) : color(c)
	{
	};

	Polygon(const Points& v, const Color& c = Palette::White) : points(v), color(c)
	{
	};

	virtual void Draw(const SDLApplication* app) const;

	virtual void Shift(const Vector2D& v);

	void Add(const Point2D& p);

	void Clear();

	virtual ~Polygon(void);
};

#endif
