#ifndef INTERSECTIONRESULT_H
#define INTERSECTIONRESULT_H

namespace RT
{
	struct IntersectionResult
	{
		bool Exists;
		Point3D Point;
		NormalizedVector3D n;

		IntersectionResult() : Exists(false)
		{
		}

		IntersectionResult(const Point3D& _Point, const NormalizedVector3D& _n) : Exists(true), Point(_Point), n(_n)
		{
		}
	};
}

#endif
