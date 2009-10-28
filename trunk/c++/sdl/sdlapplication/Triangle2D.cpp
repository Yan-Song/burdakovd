#include "Triangle2D.h"
#include "Segment.h"
#include "SDLApplication.h"

Triangle2D::~Triangle2D(void)
{
}

void Triangle2D::Draw(const SDLApplication* app, const Vector& base) const
{
	app->DrawSegment(base + Center + A, base + Center + B, color);
	app->DrawSegment(base + Center + B, base + Center + C, color);
	app->DrawSegment(base + Center + C, base + Center + A, color);
}
