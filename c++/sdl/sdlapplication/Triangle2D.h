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
	public Polygon
{
private:
	void Add(const Point2D& p) // ����� �� ���� ����� �����
	{
		Polygon::Add(p);
	};

public:
	Triangle2D(const Vector2D& a, const Vector2D& b, const Vector2D& c, const Color& _color = Palette::White, const bool filled = false)
		: Polygon(_color, filled)
	{
		Polygon::Add(a);
		Polygon::Add(b);
		Polygon::Add(c);
	}
};

#endif
