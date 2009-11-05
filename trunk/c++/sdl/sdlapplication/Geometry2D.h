#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H

#include "Vector.h"

namespace Geometry2D
{
	// ������������ �� ������� AB � CD
	bool hasIntersection(const Point2D& A, const Point2D& B,  const Point2D& C, const Point2D& D);

	// ����� ����������� �������� AB � CD, ���� ����, ����� exception
	Point2D Intersection(const Point2D& A, const Point2D& B,  const Point2D& C, const Point2D& D);
}

#endif
