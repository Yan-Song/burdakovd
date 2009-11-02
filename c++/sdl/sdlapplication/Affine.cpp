#include "Affine.h"

GenericMatrix<3> Affine::Rotate2D(const double phi, const Vector2D& center)
{
	GenericMatrix<3> m;

	m[0][0] = cos(phi);
    m[0][1] = sin(phi);
    m[1][0] = - sin(phi);
    m[1][1] = cos(phi);
    m[2][2] = 1;

	// сместить центр в начало координат, затем вращение, затем сместить обратно, (справа налево)
	return Move(center) * m * Move(-center);
}
