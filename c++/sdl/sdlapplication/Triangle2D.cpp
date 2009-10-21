#include "Triangle2D.h"
#include "Segment.h"
#include "SDLApplication.h"

Triangle2D::~Triangle2D(void)
{
}

void Triangle2D::Draw(const SDLApplication* app) const
{
	app->DrawSegment(A, B, color);
	app->DrawSegment(B, C, color);
	app->DrawSegment(C, A, color);
}

void Triangle2D::Shift(const Vector2D &v)
{
	A += v;
	B += v;
	C += v;
}
