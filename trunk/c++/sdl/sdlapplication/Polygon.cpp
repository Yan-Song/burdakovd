#include <vector>
#include "Affine.h"
#include "CompoundObject.h"
#include "FillPolygon.h"
#include "Matrix.h"
#include "Polygon.h"
#include "Projection.h"
#include "SDLApplication.h"
#include "Triangle3D.h"
#include "Vector.h"

class Polygon2D::PixelDrawer
{
private:
	const SDLApplication* const app;
	const Color& color;
	
	PixelDrawer operator=(const PixelDrawer& );

public:
	PixelDrawer(const SDLApplication* const _app, const Color& _color) : app(_app), color(_color) {};

	inline void operator ()(const int x, const int y) const
	{
		app->RawDrawPixel(x, y, color);
	}
};

class Polygon2D::PointsTransformer
{
private:
	const Vector2D offset;

	PointsTransformer operator=(const PointsTransformer& );

public:
	PointsTransformer(const Vector2D& _offset) : offset(_offset) {};

	inline ScreenPoint operator ()(const Point2D& point) const
	{
		return static_cast<ScreenPoint>(offset + point);
	}
};

void Polygon2D::Draw(SDLApplication* const app, const Vector& base) const
{
	if(Filled)
	{
		app->Lock();

		std::vector<ScreenPoint> spoints(points.size());
		// переводим их в абсолютные координаты и заодно в целочисленные
		std::transform(points.begin(), points.end(), spoints.begin(), PointsTransformer(base + Center));
		FillPolygon(spoints, ScreenPointByCoords(app->Screen->w, app->Screen->h), PixelDrawer(app, color));
		
		app->Unlock();
	}
	else
	{
		for(unsigned int i = 0; i < points.size(); ++i)
			app->DrawSegment(base + Center + points[i], base + Center + points[(i+1) % points.size()], color);
	}
}

void Polygon2D::Add(const Point2D &p)
{
	points.push_back(p);
}

void Polygon2D::Clear()
{
	points.clear();
}

void Polygon2D::Rotate(const double phi)
{
	// точки повращать относительно центра, в их координатах это 0
	GenericMatrix<3> rotator = Affine::Rotate2D(phi, Vector00);

	for(unsigned int i = 0; i < points.size(); ++i)
		points[i] = rotator * points[i];
}

void Polygon2D::Scale(const Vector2D& coefficients)
{
	for(unsigned int i = 0; i < points.size(); ++i)
		points[i] = zipWithMultiplication(points[i], coefficients);
}


void Polygon3D::Add(const Point3D& point)
{
	++vcount;

	if(vcount == 1)
		first = point;

	if(vcount > 2)
		CompoundObject3D::Add(new Triangle3D(first, last, point, color));

	last = point;
}
