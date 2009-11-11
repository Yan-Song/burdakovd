#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include "Triangle.h"
#include "sdlapplication/Utils.h"
#include "sdlapplication/Vector.h"
#include "Equation.h"
#include "ITracer.h"
#include "sdlapplication/Affine.h"

RT::Triangle::Triangle(const Point3D &pa, const Point3D &pb, const Point3D &pc, const RealColor &_color) :
RTObject(Vector000, _color), A(pa), B(pb), C(pc)
{
	// ����� �����, ��������� ����� ������������ ����� � ����� ����������� ���������� ���������������
	// http://ru.wikipedia.org/wiki/���������_����������

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

	// ��� ������������ �� ������, ����
	// 1) ���������� �� ������ �� ���� <= R (�� ���� ������ ����������� �� ������) �
	// 2) ������ ��������� � ������� ����� ���� 3) ��������� ����� ������ �����
	return (qdistance <= QR) && ((v * SC > 0) || (Center.QDistance(ray.Start) < QR));
}

class TriangleTracer : public RT::ITracer
{
private:
	const RT::NormalizedVector3D n;
	const RealColor color;
	const RT::Ray ray;

public:
	TriangleTracer(const RT::NormalizedVector3D& _n, const RealColor& _color, const RT::Ray& _ray) : n(_n), color(_color), ray(_ray)
	{
	}

	virtual RealColor Trace()
	{
		return color * abs(static_cast<Vector3D>(n) * static_cast<Vector3D>(ray.Vector));
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
		// ����� � ���������� ������������ �������, �������� ���������, ����������� �� ��� ������������
		const Point3D p = ray.Start + t * v;
		
		const Vector3D n = (B - A) ^ (C - A);

		// ��� ����������� ���� ������� ������������� ABC, pBC, ApC, ABp ������������

		if( ((B - p) ^ (C - p)) * n > 0
			&&
			((p - A) ^ (C - A)) * n > 0
			&&
			((B - A) ^ (p - A)) * n > 0
			)
		{
			return RT::Intersection(p, RT::SharedTracer(new TriangleTracer(n, color, ray)));
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
