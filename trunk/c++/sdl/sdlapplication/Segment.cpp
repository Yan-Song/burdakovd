#include "Segment.h"
#include <SDL.h>
#include "SDLApplication.h"
#include "Vector.h"
#include "Affine.h"

void Segment2D::Draw(const SDLApplication* app, const Vector& base) const
{
	app->DrawSegment(base + Center + A, base + Center + B, color);
}

void Segment2D::Rotate(const double phi)
{
	A = Affine::Rotate2D(phi) * A;

	B = Affine::Rotate2D(phi) * B;
}
