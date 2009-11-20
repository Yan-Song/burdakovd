#ifndef PLANE_H
#define PLANE_H

#include <sdlapplication/Vector.h>
#include "Material.h"
#include "NormalizedVector3D.h"
#include "RTObject.h"

namespace RT
{
	// плоскость, заданная уравнением p = Center + a * du + b * dv
	class Plane : public RTObject
	{
	private:
		class Tracer;
		Vector3D du;
		Vector3D dv;

	public:
		Plane(const Point3D& center, const Vector3D& _du, const Vector3D& _dv, const Material& _material) :
		  RTObject(center, _material), du(_du), dv(_dv)
		  {
		  }

		virtual void Move(const Vector3D& offset)
		{
			Center += offset;
		}

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi)
		{
			Center = Affine::Rotate3D(axe, phi, base) * Center;

			GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi);
			du = rotator * du;
			dv = rotator * dv;
		}

		virtual bool PossibleIntersection(const RT::Ray& ) const
		{
			return true;
		}

		virtual MaybeIntersection FindIntersection(const RT::Ray& ray) const;
	};
}

#endif
