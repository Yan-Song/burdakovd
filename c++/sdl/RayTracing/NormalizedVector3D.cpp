#include "NormalizedVector3D.h"
#include "Utils.h"
#include <cmath>

RT::NormalizedVector3D::NormalizedVector3D(const double x, const double y, const double z)
{
	const double length = sqrt(sqr(x) + sqr(y) + sqr(z));

	if(length == 0)
		throw new std::invalid_argument("Can't normalize Vector of length 0.0");

	data[0] = x / length;
	data[1] = y / length;
	data[2] = z / length;
}

RT::NormalizedVector3D::NormalizedVector3D(const Vector3D &vector)
{
	const double x = vector[0], y = vector[1], z = vector[2];

	const double length = sqrt(sqr(x) + sqr(y) + sqr(z));

	if(length == 0)
		throw new std::invalid_argument("Can't normalize Vector of length 0.0");

	data[0] = x / length;
	data[1] = y / length;
	data[2] = z / length;
}

RT::NormalizedVector3D::NormalizedVector3D()
{
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
}
