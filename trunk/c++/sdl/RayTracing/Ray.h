#ifndef RAY_H
#define RAY_H

#include "Vector.h"

namespace RT
{
	class Ray
	{
	private:
		Vector3D Vector;
		Point3D Start;

	public:
		Ray(const Vector3D& _Vector, const Point3D& _Start)
			: Vector(_Vector), Start(_Start) {}
	};
}

#endif
