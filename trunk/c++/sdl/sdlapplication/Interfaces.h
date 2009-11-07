#ifndef INTERFACES_H
#define INTERFACES_H

#include "Vector.h"
#include "Color.h"

// класс, умеющий рисовать треугольники
class ITriangleDrawer
{
public:
	virtual void DrawTriangle(const Vector3D& A, const Vector3D& B, const Vector3D& C, const Color& color) = 0;
	virtual ~ITriangleDrawer() {}
};

#endif
