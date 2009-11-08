#include "Sphere.h"
#include "Vector.h"

bool RT::Sphere::CheckIntersection(const RT::Ray &ray) const
{
	const Vector3D SC = Center - ray.Start;
	const Vector3D v = ray.Vector;
	const double distance = (v ^ SC).Length();

	// луч пересекается со сферой, если
	// 1) расстояние от центра до него <= R (то есть прямая перескается со сферой) и
	// 2) вектор направлен в сторону сферы либо 3) начальная точка внутри сферы
	return (distance <= R) && ((v * SC > 0) || (Center.Distance(ray.Start) < R));
}
