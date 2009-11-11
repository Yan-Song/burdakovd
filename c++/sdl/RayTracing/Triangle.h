#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "RTObject.h"

namespace RT
{
	class Triangle : public RTObject
	{
	private:
		double QR; // квадрат радиуса
		double R; // радиус сферы, описанной около треугольника
		Point3D A, B, C;

	public:
		Triangle(const Point3D& pa, const Point3D& pb, const Point3D& pc, const RealColor& _color);

		virtual bool PossibleIntersection(const Ray& ray) const;

		virtual MaybeIntersection FindIntersection(const Ray& ray) const;
		
		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi);

		virtual void Move(const Vector3D& offset);
	};
}

#endif
