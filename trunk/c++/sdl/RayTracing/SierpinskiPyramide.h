#ifndef SIERPINSKIPYRAMIDE_H
#define SIERPINSKIPYRAMIDE_H

#include "RTObject.h"
#include "CompoundObject.h"
#include "sdlapplication/Vector.h"
#include "Sphere.h"

namespace RT
{
	class SierpinskiPyramide : public CompoundObject
	{
	private:
		CompoundObject::SharedObject sphere;

	public:
		SierpinskiPyramide(const Point3D& center, const double edgeLength, const int iterations, const Material& material);

		virtual bool PossibleIntersection(const Ray& ray) const;
	};
}

#endif
