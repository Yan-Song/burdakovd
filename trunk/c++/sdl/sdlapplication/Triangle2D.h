#ifndef TRAINGLE_H
#define TRIANGLE_H

#include "GraphObject.h"
#include "SDLApplication.h"
#include "Vector.h"
#include "Color.h"
#include "Polygon.h"

// � ������� ��� ������� �������� ��� �������������� �����������
// ������������, ��� ������ ��� - ��� ��� �������������� ����� Add, �� ������� ���� ������ �������������� �� Polygon ����� Add � �� �����

class Triangle2D :
	public Polygon2D
{
private:
	void Add(const Point2D& p) // ����� �� ���� ����� �����
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
