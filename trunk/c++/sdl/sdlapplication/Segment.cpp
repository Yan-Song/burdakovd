#include "Segment.h"
#include <SDL.h>
#include "SDLApplication.h"
#include "Vector.h"
#include "Affine.h"
#include "Projection.h"

void Segment2D::Draw(SDLApplication* const app, const Vector& base) const
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
	A = zipWithMultiplication(A, coefficients);
	B = zipWithMultiplication(B, coefficients);
}
