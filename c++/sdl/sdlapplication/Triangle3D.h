#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "GraphObject.h"
#include "Interfaces.h"
#include "Vector.h"
#include "Color.h"

class Triangle3D : public GraphObject3D
{
public:
	Point3D A, B, C;
	Color color;

	Triangle3D(const Point3D& a, const Point3D& b, const Point3D& c, const Color& _color = Palette::White) :
		A(a), B(b), C(c), color(_color) {}

	virtual void Scale(const Vector3D& coefficients);

	virtual void Draw(const Vector3D& base, ITriangleDrawer* const drawer) const;

	virtual void Rotate(const Affine::Axe axe, const double phi);
};

#endif