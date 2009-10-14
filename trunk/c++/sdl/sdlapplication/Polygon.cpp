#include "Polygon.h"
#include "sdlapplication.h"
#include "Vector.h"

Polygon::~Polygon(void)
{
}

void Polygon::Draw(const SDLApplication *app) const
{
	if(points.size()==0)
		return;

	for(unsigned int i = 0; i < points.size(); ++i)
		app->DrawSegment(points[i], points[(i+1) % points.size()], color);
}

void Polygon::Shift(const Vector2D &v)
{
	for(Points::iterator it = points.begin(); it != points.end(); ++it)
		(*it) += v;
}

void Polygon::Add(const Point2D &p)
{
	points.push_back(p);
}

void Polygon::Clear()
{
	points.clear();
}
