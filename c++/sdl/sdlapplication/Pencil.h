#ifndef PENCIL_H
#define PENCIL_H

#include "CompoundObject.h"
#include "Color.h"
#include "Vector.h"

class Pencil : public CompoundObject3D
{
public:
	Pencil(const Vector3D& center, const double length, const Color& outside, const Color& wood, const Color& inside);
};

#endif