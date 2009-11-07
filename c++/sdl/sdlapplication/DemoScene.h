#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CompoundObject.h"
#include "Vector.h"

class DemoScene : public CompoundObject3D
{
public:
	DemoScene(const Vector3D& center);
};

#endif