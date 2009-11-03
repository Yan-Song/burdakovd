#include "Polygon.h"
#include "SDLApplication.h"
#include "Vector.h"
#include "Affine.h"
#include "Matrix.h"

void Polygon::Draw(const SDLApplication *app, const Vector& base) const
{
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

void Polygon::Rotate(const double phi)
{
	// точки повращать относительно центра, в их координатах это 0
	GenericMatrix<3> rotator = Affine::Rotate2D(phi, Vector00);

	for(unsigned int i = 0; i < points.size(); ++i)
		points[i] = rotator * points[i];
}

void Polygon::Scale(const Vector2D& coefficients)
{
	for(unsigned int i = 0; i < points.size(); ++i)
		for(unsigned int j = 0; j < coefficients.Dimensions; ++j)
			points[i][j] *= coefficients[j];
}
