#ifndef PYRAMID_H
#define PYRAMID_H

#include "Frustum.h"

// пирамида: частный случай усеченной пирамиды
class Pyramid : public Frustum
{
public:
	Pyramid(const Vector3D& center, const double R, const double H, const int precision, const Color& color)
		: Frustum(center, R, 0, H, precision, color)
	{
	}
};

#endif
