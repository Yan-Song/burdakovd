#ifndef SPHERE_H
#define SPHERE_H

#include "RTObject.h"
#include "IntersectionResult.h"
#include "sdlapplication/Color.h"
#include "sdlapplication/Affine.h"
#include "sdlapplication/Utils.h"

namespace RT
{
	class Sphere : public RTObject
	{
	private:
		class Tracer;
		const double QR;

	public:
		const double R;

		Sphere(const Vector3D& center, const double r, const RealColor& _color) : RTObject(center, _color), QR(sqr(r)), R(r)
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
