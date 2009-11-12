#ifndef CUBE_H
#define CUBE_H

#include "CompoundObject.h"
#include "Sphere.h"
#include "Material.h"
#include "Tetragon.h"

namespace RT
{
	class Cube : public CompoundObject
	{
	private:
		RT::Sphere sphere;

	public:
		Cube(const Point3D& center, const double edgeLength, const Material& material)
			: sphere(center, 0.5 * sqrt(3.0) * edgeLength, material)
		{
			const double a = edgeLength;

			const Point3D A = center + 0.5 * Vector3DByCoords(-a, -a, -a);
			const Point3D b = center + 0.5 * Vector3DByCoords(-a, a, -a);
			const Point3D c = center + 0.5 * Vector3DByCoords(a, a, -a);
			const Point3D d = center + 0.5 * Vector3DByCoords(a, -a, -a);

			const Point3D e = center + 0.5 * Vector3DByCoords(-a, -a, a);
			const Point3D f = center + 0.5 * Vector3DByCoords(-a, a, a);
			const Point3D g = center + 0.5 * Vector3DByCoords(a, a, a);
			const Point3D h = center + 0.5 * Vector3DByCoords(a, -a, a);

			CompoundObject::Add(CompoundObject::SharedObject(new Tetragon(A, b, c, d, material)));
			CompoundObject::Add(CompoundObject::SharedObject(new Tetragon(e, f, g, h, material)));

			CompoundObject::Add(CompoundObject::SharedObject(new Tetragon(A, b, f, e, material)));
			CompoundObject::Add(CompoundObject::SharedObject(new Tetragon(b, c, g, f, material)));
			CompoundObject::Add(CompoundObject::SharedObject(new Tetragon(c, d, h, g, material)));
			CompoundObject::Add(CompoundObject::SharedObject(new Tetragon(d, A, e, h, material)));
		}

		virtual void Move(const Vector3D& offset)
		{
			CompoundObject::Move(offset);
			sphere.Move(offset);
		}

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi)
		{
			CompoundObject::Rotate(axe, base, phi);
			sphere.Rotate(axe, base, phi);
		}

		virtual bool PossibleIntersection(const RT::Ray& ray) const
		{
			return sphere.PossibleIntersection(ray);
		}

	};
}

#endif
