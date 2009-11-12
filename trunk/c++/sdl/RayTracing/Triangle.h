#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "RTObject.h"
#include "Material.h"

namespace RT
{
	class Triangle : public RTObject
	{
	private:
		double QR; // квадрат радиуса
		double R; // радиус сферы, описанной около треугольника
		Point3D A, B, C;

	public:
		// dx - ab, dy - ac, base - a
		Triangle(const Point3D& pa, const Point3D& pb, const Point3D& pc, const Material& _material);

		virtual bool PossibleIntersection(const Ray& ray) const;

		virtual MaybeIntersection FindIntersection(const Ray& ray) const;
		
		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi);

		virtual void Move(const Vector3D& offset);
	};
}

#endif
