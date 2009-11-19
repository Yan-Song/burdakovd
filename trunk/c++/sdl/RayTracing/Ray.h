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

		Ray(const NormalizedVector3D& _Vector, const Point3D& _Start) : Vector(_Vector), Start(_Start)
		{
		}
	};
}

#endif