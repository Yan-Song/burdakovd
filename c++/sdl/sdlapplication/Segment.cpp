#include "Segment.h"
#include <SDL.h>
#include "SDLApplication.h"
#include "Vector.h"

void Segment2D::Draw(const SDLApplication* app, const Vector& base) const
{
	app->DrawSegment(base + Center + A, base + Center + B, color);
}
