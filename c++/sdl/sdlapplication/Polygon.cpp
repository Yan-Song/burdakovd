#include "Polygon.h"
#include "SDLApplication.h"
#include "Vector.h"
#include "Affine.h"
#include "Matrix.h"
#include "FillPolygon.h"
#include <vector>
#include "Projection.h"

class PixelDrawer
{
private:
	const SDLApplication* app;
	const Color& color;

public:
	PixelDrawer(const SDLApplication* _app, const Color& _color) : app(_app), color(_color) {};

	inline void operator ()(const int x, const int y) const
	{
		app->DrawPixel(x, y, color);
	}
};

class PointsTransformer
{
private:
	const Vector2D offset;

public:
	PointsTransformer(const Vector2D& _offset) : offset(_offset) {};

	inline ScreenPoint operator ()(const Point2D& point) const
	{
		return static_cast<ScreenPoint>(offset + point);
	}
};

void Polygon2D::Draw(const SDLApplication *app, const Vector& base) const
{
	if(Filled)
	{
		std::vector<ScreenPoint> spoints(points.size());
		// переводим их в абсолютные координаты и заодно в целочисленные
		std::transform(points.begin(), points.end(), spoints.begin(), PointsTransformer(base + Center));
		FillPolygon(spoints, ScreenPointByCoords(app->Screen->w, app->Screen->h), PixelDrawer(app, color));
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
		points[i] *= coefficients;
}

void Polygon3D::Draw(const SDLApplication *app, const Vector3D &base) const
{
	unsigned int n = points.size();

	Projection::Matrix projection = Projection::OrthographicYProjection();

	std::vector<ScreenPoint> spoints(n);

	for(unsigned int i = 0; i < n; ++i)
		spoints[i] = Projection::GetXZ(projection * (base + Center + points[i]));

	for(unsigned int i = 0; i < n; ++i)
			app->DrawSegment(spoints[i], spoints[(i+1) % n], color);
}

void Polygon3D::Rotate(const int axe, const double phi)
{
	GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi);

	for(unsigned int i = 0; i < points.size(); ++i)
		points[i] = rotator * points[i];
}

void Polygon3D::Scale(const Vector3D &coefficients)
{
	for(unsigned int i = 0; i < points.size(); ++i)
		points[i] *= coefficients;
}

void Polygon3D::Add(const Point3D& point)
{
	points.push_back(point);
}
