#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H

#include "Vector.h"

namespace Geometry2D
{
	// пересекаются ли отрезки AB и CD
	bool hasIntersection(const Point2D& A, const Point2D& B,  const Point2D& C, const Point2D& D);

	// точка пересечения отрезков AB и CD, если есть, иначе exception
	Point2D Intersection(const Point2D& A, const Point2D& B,  const Point2D& C, const Point2D& D);
}

#endif
