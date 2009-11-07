#ifndef TETRAGON_H
#define TETRAGON_H

#include "Polygon.h"
#include "Color.h"
#include "Vector.h"

// Четырехугольник.
// вершины задавать в порядке обхода против часовой стрелки
class Tetragon : public Polygon3D
{
public:
	Tetragon(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Color& _color);
};

#endif