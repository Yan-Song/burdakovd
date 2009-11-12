#include "Sphere.h"
#include "sdlapplication/Vector.h"
#include "Polynom.h"
#include "Equation.h"
#include "ITracer.h"
#include "sdlapplication/Utils.h"
#include <cmath>
#include "Material.h"

bool RT::Sphere::PossibleIntersection(const RT::Ray &ray) const
{
	const Vector3D SC = Center - ray.Start;
	const Vector3D v = ray.Vector;
	const double qdistance = (v ^ SC).QLength();

	// луч пересекается со сферой, если
	// 1) расстояние от центра до него <= R (то есть прямая перескается со сферой) и
	// 2) вектор направлен в сторону сферы либо 3) начальная точка внутри сферы
	return (qdistance <= QR) && ((v * SC > 0) || (Center.QDistance(ray.Start) < QR));
}

class RT::Sphere::Tracer : public RT::ITracer
{
private:
	const RT::Ray ray;
	const Point3D point;
	const Material material;
	const Point3D center;
	const Vector3D rx, ry, rz;

public:
	Tracer(const RT::Ray& _ray, const Point3D& _point, const Material& _material, const Point3D& _center,
		const Vector3D& _rx, const Vector3D& _ry, const Vector3D& _rz)
		: ray(_ray), point(_point), material(_material), center(_center), rx(_rx), ry(_ry), rz(_rz) {}

	virtual RealColor Trace()
	{
		const double R = center.Distance(point);
		const Vector3D rv = point - center;
		const RT::NormalizedVector3D n = rv;

		const double x = rv * rx / sqr(R);
		const double y = rv * ry / sqr(R);
		const double z = rv * rz / sqr(R);

		const double teta = acos(z);
		const double phi_ = (sqr(x) + sqr(y) == 0) ? 0 : acos(x / sqrt(sqr(x) + sqr(y)));
		const double phi = y < 0  ?  2 * Pi - phi_  :  phi_;
		

		return material.Trace(point, Vector2DByCoords(phi * R, teta * R), n, ray);
	}
};

RT::MaybeIntersection RT::Sphere::FindIntersection(const RT::Ray &ray) const
{
	typedef GenericVector<RT::Polynom, 3> PolyVector;

	// две точки пересечения (с прямой, содержащей луч) можно найти, решив уравнение Center.Distance(ray.Start + t * ray.Vector) = R
	// возвести обе части в квадрат
	// получится Center.QDistance(start + t * v) - sqr(R) = 0
	// (Center - start).QDistance(t * v) - sqr(R)
	// (SC - t * v, SC - t * v) - sqr(R) = (SC, SC) - sqr(R) - 2 * t * (SC, v) + (v, v) * t * t, (v, v) == 1

	const Vector3D SC = Center - ray.Start;	
	const Vector3D v = ray.Vector;
	
	// составляем уравнение
	Polynom equation(1.0, 2);
	equation.SetCoefficient(1, - 2 * (SC * v));
	equation.SetCoefficient(0, SC * SC - QR);

	// пытаемся решить его
	double t1, t2;
	try
	{
		const std::pair<double, double> roots = SolveSquareEquation(equation);
		t1 = roots.first;
		t2 = roots.second;
	}
	catch(const std::invalid_argument&)
	{
		// нет решений
		return NoIntersection();
	}

	double t;

	// выбираем ближайшую точку пересечения, но с положительным t
	// отрицательные t - это не интересующая нас полупрямая
	if(t1 < 0)
		if(t2 < 0)
			return NoIntersection();
		else
			t = t2;
	else
		if(t2 < 0)
			t = t1;
		else
			t = std::min(t1, t2);

	const Point3D point = ray.Start + t * v;

	const SharedTracer tracer = SharedTracer(new Tracer(ray, point, material, Center, rx, ry, rz));

	return Intersection(point, tracer);
}

