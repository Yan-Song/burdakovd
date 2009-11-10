#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "sdlapplication/Vector.h"
#include "sdlapplication/Affine.h"

namespace RT
{
	class IObject3D
	{
	public:
		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi) = 0;

		virtual void Move(const Vector3D& offset) = 0;

		virtual ~IObject3D() {}
	};
}

#endif
