#include "Polygon.h"
#include "SDLApplication.h"
#include "Vector.h"

Polygon::~Polygon(void)
{
}

void Polygon::Draw(const SDLApplication *app, const Vector& base) const
{
	if(points.size()==0)
		return;

	for(unsigned int i = 0; i < points.size(); ++i)
		app->DrawSegment(base + Center + points[i], base + Center + points[(i+1) % points.size()], color);
}

void Polygon::Add(const Point2D &p)
{
	points.push_back(p);
}

void Polygon::Clear()
{
	points.clear();
}
