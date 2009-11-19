#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "RTObject.h"
#include "CompoundObject.h"
#include "Sphere.h"

namespace RT
{
	class Frustum : public CompoundObject
	{
	private:
		CompoundObject::SharedObject sphere; // Ограничивающая сфера
		bool has_sphere;

	public:
		Frustum(const Vector3D &CenterBottom, const double RBottom, const double RTop, const double H, const int count, const Material &material);

		virtual bool PossibleIntersection(const Ray& ray) const;

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi);

		virtual void Move(const Vector3D& offset);
	};
}

#endif
