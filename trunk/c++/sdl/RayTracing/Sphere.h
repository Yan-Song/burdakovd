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
		Vector3D rx, ry, rz;

	public:
		const double R;

		Sphere(const Vector3D& center, const double r, const Material& _material) : RTObject(center, _material), QR(sqr(r)), R(r),
			rx(Vector3DByCoords(r, 0, 0)), ry(Vector3DByCoords(0, r, 0)), rz(Vector3DByCoords(0, 0, r))
		{
		}

		virtual bool PossibleIntersection(const Ray& ray) const;

		virtual MaybeIntersection FindIntersection(const Ray& ray) const;

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi)
		{
			GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi, base);
			Center = rotator * Center;

			GenericMatrix<4> nrotator = Affine::Rotate3D(axe, phi, Vector000);
			rx = nrotator * rx;
			ry = nrotator * ry;
			rz = nrotator * rz;
		}

		virtual void Move(const Vector3D& offset)
		{
			Center += offset;
		}
	};
}

#endif
