#include "Tetragon.h"
#include "Polygon.h"
#include "Color.h"
#include "Vector.h"

Tetragon::Tetragon(const Vector3D &a, const Vector3D &b, const Vector3D &c, const Vector3D &d, const Color &_color) :
	Polygon3D(_color)
{
	Polygon3D::Add(a);
	Polygon3D::Add(b);
	Polygon3D::Add(c);
	Polygon3D::Add(d);
}