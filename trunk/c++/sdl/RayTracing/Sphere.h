#ifndef SPHERE_H
#define SPHERE_H

#include "RTObject.h"
#include "IntersectionResult.h"
#include "Color.h"

namespace RT
{
	class Sphere : public RTObject
	{
	public:
		Vector3D Center;
		double R;

		Sphere(const Vector3D& center, const double r, const RealColor& _color) : RTObject(_color), Center(center), R(r)
		{
		}

		virtual bool MaybeIntersection(const Ray& ray) const;

		virtual IntersectionResult FindIntersection(const Ray& ray) const;

		virtual RealColor Trace(const Ray& ray, const IntersectionResult& result) const;
	};
}

#endif
