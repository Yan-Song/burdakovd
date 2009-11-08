#ifndef SPHERE_H
#define SPHERE_H

#include "IRTObject.h"

namespace RT
{
	class Sphere : public IRTObject
	{
	public:
		Vector3D Center;
		double R;

		Sphere(const Vector3D& center, const double r) : Center(center), R(r)
		{
		}

		virtual bool CheckIntersection(const Ray& ray) const;
	};
}

#endif
