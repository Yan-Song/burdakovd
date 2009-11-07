#ifndef PRISM_H
#define PRISM_H

#include "Frustum.h"

// призма: частный случай усеченной пирамиды
class Prism : public Frustum
{
public:
	Prism(const Vector3D& center, const double R, const double H, const int precision, const Color& color)
		: Frustum(center, R, R, H, precision, color)
	{
	}
};

#endif
