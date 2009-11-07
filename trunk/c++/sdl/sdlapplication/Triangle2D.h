#ifndef TRAINGLE_H
#define TRIANGLE_H

#include "GraphObject.h"
#include "SDLApplication.h"
#include "Vector.h"
#include "Color.h"
#include "Polygon.h"

// к счастью тут удалось обойтись без множественного наледования
// единственное, что портит вид - так это неиспользуемый метод Add, но лучшего пути скрыть унаследованный от Polygon метод Add я не видел

class Triangle2D :
	public Polygon2D
{
private:
	void Add(const Point2D& p) // чтобы не была видна извне
	{
		Polygon2D::Add(p);
	};

public:
	Triangle2D(const Vector2D& a, const Vector2D& b, const Vector2D& c, const Color& _color = Palette::White, const bool filled = false)
		: Polygon2D(_color, filled)
	{
		Polygon2D::Add(a);
		Polygon2D::Add(b);
		Polygon2D::Add(c);
	}
};

#endif
