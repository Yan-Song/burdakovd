#include <cmath>
#include <sdlapplication/Vector.h>
#include "Invisible.h"
#include "SierpinskiPyramide.h"
#include "Triangle.h"

RT::SierpinskiPyramide::SierpinskiPyramide(const Point3D &center, const double edgeLength, const int iterations, const Material &material) :
	sphere()
{
	assert(edgeLength > 0);
	
	const double a = edgeLength;
	const double H = sqrt(2.0 / 3.0) * a;
	const double r = a / sqrt(3.0);
	const double h = (sqr(H) - sqr(r)) / 2 / H;
	const double R = sqrt(sqr(r) + sqr(h));

	const Point3D O = center;
	const Point3D A = O + Vector3DByCoords(r * cos(0.0), r * sin(0.0), -h);
	const Point3D B = O + Vector3DByCoords(r * cos(2 * Pi / 3.0), r * sin(2 * Pi / 3.0), -h);
	const Point3D C = O + Vector3DByCoords(r * cos(4 * Pi / 3.0), r * sin(4 * Pi / 3.0), -h);
	const Point3D D = O + Vector3DByCoords(0, 0, H - h);

	sphere = CompoundObject::SharedObject(new RT::Sphere(center, R, material));
	CompoundObject::Add(CompoundObject::SharedObject(new RT::Invisible(sphere)));

	if(iterations == 0)
	{
		// конец рекурсии, строим тетраэдр из четырёх треугольников
		CompoundObject::Add(CompoundObject::SharedObject(new RT::Triangle(A, B, C, material)));
		CompoundObject::Add(CompoundObject::SharedObject(new RT::Triangle(A, B, D, material)));
		CompoundObject::Add(CompoundObject::SharedObject(new RT::Triangle(A, D, C, material)));
		CompoundObject::Add(CompoundObject::SharedObject(new RT::Triangle(D, B, C, material)));
	}
	else
	{
		// делаем четыре таких же объекта но меньше размером
		CompoundObject::Add(CompoundObject::SharedObject(new SierpinskiPyramide((O + A) / 2.0, edgeLength / 2, iterations - 1, material)));
		CompoundObject::Add(CompoundObject::SharedObject(new SierpinskiPyramide((O + B) / 2.0, edgeLength / 2, iterations - 1, material)));
		CompoundObject::Add(CompoundObject::SharedObject(new SierpinskiPyramide((O + C) / 2.0, edgeLength / 2, iterations - 1, material)));
		CompoundObject::Add(CompoundObject::SharedObject(new SierpinskiPyramide((O + D) / 2.0, edgeLength / 2, iterations - 1, material)));
	}
}

bool RT::SierpinskiPyramide::PossibleIntersection(const RT::Ray &ray) const
{
	return sphere->PossibleIntersection(ray);
}
