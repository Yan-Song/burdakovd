#ifndef TRACEVECTOR_H
#define TRACEVECTOR_H

#include "Vector.h"

namespace RT
{
	class TraceVector
	{
	private:
		Vector3D Vector;
		Point3D StartPoint;

	public:
		TraceVector(const Vector3D& _Vector, const Point3D& _StartPoint)
			: Vector(_Vector), StartPoint(_StartPoint) {}
	};
}

#endif
