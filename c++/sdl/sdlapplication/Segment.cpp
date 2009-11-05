#include "Segment.h"
#include <SDL.h>
#include "SDLApplication.h"
#include "Vector.h"
#include "Affine.h"
#include "Projection.h"

void Segment2D::Draw(const SDLApplication* app, const Vector& base) const
{
	app->DrawSegment(base + Center + A, base + Center + B, color);
}

void Segment2D::Rotate(const double phi)
{
	A = Affine::Rotate2D(phi) * A;

	B = Affine::Rotate2D(phi) * B;
}

void Segment2D::Scale(const Vector2D& coefficients)
{
	A *= coefficients;
	B *= coefficients;
}


void Segment3D::Scale(const Vector3D &coefficients)
{
	A *= coefficients;
	B *= coefficients;
}

void Segment3D::Draw(const SDLApplication *app, const Vector3D &base) const
{
	Projection::Matrix projection = Projection::OrthographicYProjection();

	Point2D a = Projection::GetXZ(projection * (base + Center + A));
	Point2D b = Projection::GetXZ(projection * (base + Center + B));

	app->DrawSegment(a, b, color);
}

void Segment3D::Rotate(const int axe, const double phi)
{
	GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi);
	A = rotator * A;
	B = rotator * B;
}
