#ifndef RAY_H
#define RAY_H

#include "NormalizedVector3D.h"
#include "sdlapplication/Utils.h"

namespace RT
{
	class Ray
	{
	public:
		NormalizedVector3D Vector;
		Point3D Start;
		double Power;

		Ray(const NormalizedVector3D& _Vector, const Point3D& _Start, const double _power = 1.0) : \
			Vector(_Vector), Start(_Start), Power(_power)
		{
		}
	};
}

#endif
