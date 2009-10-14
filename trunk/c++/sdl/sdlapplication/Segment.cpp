#include "Segment.h"
#include <SDL.h>
#include "sdlapplication.h"
#include "Vector.h"

void Segment2D::Draw(const SDLApplication* app) const
{
	app->DrawSegment(A, B, color);
}

void Segment2D::Shift(const Vector2D& v)
{
	A += v;
	B += v;
}

/*void Line::Modify(const Matrix &m)
{
    A = m * A;
    B = m * B;
}*/
