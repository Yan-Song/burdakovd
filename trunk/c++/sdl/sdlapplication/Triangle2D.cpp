#include "Triangle2D.h"
#include "Segment.h"
#include "SDLApplication.h"
#include "Affine.h"
#include "Matrix.h"

Triangle2D::~Triangle2D(void)
{
}

void Triangle2D::Draw(const SDLApplication* app, const Vector& base) const
{
	app->DrawSegment(base + Center + A, base + Center + B, color);
	app->DrawSegment(base + Center + B, base + Center + C, color);
	app->DrawSegment(base + Center + C, base + Center + A, color);
}

void Triangle2D::Rotate(const double phi)
{
	GenericMatrix<3> rotator = Affine::Rotate2D(phi);

	A = rotator * A;
	B = rotator * B;
	C = rotator * C;
}
