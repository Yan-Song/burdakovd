#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include "Triangle.h"
#include "sdlapplication/Utils.h"
#include "sdlapplication/Vector.h"
#include "Equation.h"
#include "ITracer.h"
#include "sdlapplication/Affine.h"
#include "Material.h"

RT::Triangle::Triangle(const Point3D &pa, const Point3D &pb, const Point3D &pc, const Material &_material) :
RTObject(Vector000, _material), QR(), R(), A(pa), B(pb), C(pc)
{
	const double a = B.Distance(C);
	const double b = A.Distance(C);
	const double c = A.Distance(B);

	const double S = ((B - A) ^ (C - A)).Length() / 2;

	if(S == 0)
	{
		QR = R = 0;
		Center = A;
	}
	else
	{
		R = a * b * c / 4 / S;
		QR = sqr(R);
		
		const double alpha_a = sqr(a) / 8 / sqr(S) * ((A - B) * (A - C));
		const double alpha_b = sqr(b) / 8 / sqr(S) * ((B - A) * (B - C));
		const double alpha_c = sqr(c) / 8 / sqr(S) * ((C - A) * (C - B));

		Center = alpha_a * A + alpha_b * B + alpha_c * C;
	}
}

bool RT::Triangle::PossibleIntersection(const RT::Ray& ray) const
{
	const Vector3D SC = Center - ray.Start;
	const Vector3D v = ray.Vector;
	const double qdistance = (v ^ SC).QLength();

	return (qdistance <= QR) && ((v * SC > 0) || (Center.QDistance(ray.Start) < QR));
}

class TriangleTracer : public RT::ITracer
{
private:
	Point3D A, B, C;
	Point3D point;
	RT::NormalizedVector3D n;
	RT::Material material;
	RT::Ray ray;

public:
	TriangleTracer(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& _p, const RT::NormalizedVector3D& _n,
		const RT::Material& _material, const RT::Ray& _ray) :
	A(a), B(b), C(c),
	  point(_p), n(_n), material(_material), ray(_ray)
	{
	}

	virtual RealColor Trace()
	{
		const RT::NormalizedVector3D dx = B - A;
		const RT::NormalizedVector3D dy = C - A;

		const double z = (static_cast<Vector3D>(dx) ^ static_cast<Vector3D>(dy)).Length();

		const double u = ((point - A) ^ static_cast<Vector3D>(dy)).Length() / z;
		const double v = ((point - A) ^ static_cast<Vector3D>(dx)).Length() / z;

		return material.Trace(point, Vector2DByCoords(u, v), n, ray);
	}
};

RT::MaybeIntersection RT::Triangle::FindIntersection(const RT::Ray& ray) const
{
	const Vector3D v = static_cast<Vector3D>(ray.Vector);

	const Vector3D n = (B - A) ^ (C - A);

	const double distance = (A - ray.Start) * n;

	const double ddistance_dt = v * n;
	
	if(ddistance_dt == 0)
		return RT::NoIntersection();

	const double t = distance / ddistance_dt;

	if(t > 0)
	{
		const Point3D p = ray.Start + t * v;
		
		const Vector3D n = (B - A) ^ (C - A);

		if( ((B - p) ^ (C - p)) * n > 0
			&&
			((p - A) ^ (C - A)) * n > 0
			&&
			((B - A) ^ (p - A)) * n > 0
			)
		{
			return RT::Intersection(p, RT::SharedTracer(new TriangleTracer(A, B, C, p, n, material, ray)));
		}
		else
		{
			return RT::NoIntersection();
		}

		
	}
	else
		return RT::NoIntersection();
}

void RT::Triangle::Move(const Vector3D &offset)
{
	Center += offset;
	A += offset;
	B += offset;
	C += offset;
}

void RT::Triangle::Rotate(const Affine::Axe axe, const Point3D &base, const double phi)
{
	const GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi, base);

	Center = rotator * Center;
	A = rotator * A;
	B = rotator * B;
	C = rotator * C;
}

#endif
