#ifndef TETRAGON_H
#define TETRAGON_H

#include "CompoundObject.h"
#include "Triangle.h"

namespace RT
{
	class Tetragon : public CompoundObject
	{
	public:
		// текстура будет наложена так, что dx будет направлен вдоль ab
		// dy - вдоль ad
		Tetragon(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& d, const Material& material);
	};
}

#endif
