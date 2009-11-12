#ifndef CUBE_H
#define CUBE_H

#include "Vector.h"
#include "Color.h"
#include "CompoundObject.h"

class Cube : public CompoundObject3D
{
public:
	Cube(const Vector3D& center, const double edgeLength, const Color& color = Palette::White);

};

#endif
