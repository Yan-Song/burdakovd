#ifndef SPHERE_H
#define SPHERE_H

#include "RTObject.h"
#include "IntersectionResult.h"
#include "sdlapplication/Color.h"
#include "sdlapplication/Affine.h"

namespace RT
{
	class Sphere : public RTObject
	{
	public:
		const double R;

		Sphere(const Vector3D& center, const double r, const RealColor& _color) : RTObject(center, _color), R(r)
		{
		}

		virtual bool PossibleIntersection(const Ray& ray) const;

		virtual MaybeIntersection FindIntersection(const Ray& ray) const;

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi)
		{
			Center = Affine::Rotate3D(axe, phi, base) * Center;
		}

		virtual void Move(const Vector3D& offset)
		{
			Center += offset;
		}
	};
}

#endif
