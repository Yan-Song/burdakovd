#include "Sphere.h"
#include "Vector.h"
#include "Polynom.h"
#include "SquareEquation.h"

bool RT::Sphere::MaybeIntersection(const RT::Ray &ray) const
{
	const Vector3D SC = Center - ray.Start;
	const Vector3D v = ray.Vector;
	const double distance = (v ^ SC).Length();

	// ��� ������������ �� ������, ����
	// 1) ���������� �� ������ �� ���� <= R (�� ���� ������ ����������� �� ������) �
	// 2) ������ ��������� � ������� ����� ���� 3) ��������� ����� ������ �����
	return (distance <= R) && ((v * SC > 0) || (Center.Distance(ray.Start) < R));
}

typedef GenericVector<RT::Polynom, 3> PolyVector;

RT::IntersectionResult RT::Sphere::FindIntersection(const RT::Ray &ray) const
{
	// ��� ����� ����������� (� ������ ���������� ���) ����� �����, ����� ��������� Center.Distance(ray.Start + t * ray.Vector) = R
	// �������� ��� ����� � �������
	// ��������� Center.QDistance(start + t * v) - sqr(R) = 0

	const Polynom _t = Polynom(1, 1);
	const PolyVector start = ray.Start;
	const PolyVector v = static_cast<Vector3D>(ray.Vector);
	const PolyVector center = Center;

	// ���������� ���������
	Polynom equation = center.QDistance(start + _t * v) - Polynom(R * R); // == 0

	// �������� ������ ���
	double t1, t2;
	try
	{
		const std::pair<double, double> roots = SolveSquareEquation(equation);
		t1 = roots.first;
		t2 = roots.second;
	}
	catch(std::invalid_argument)
	{
		// ��� �������
		return IntersectionResult();
	}

	double t;

	// �������� ��������� ����� �����������, �� � ������������� t
	// ������������� t - ��� �� ������������ ��� ����������
	if(t1 < 0)
		if(t2 < 0)
			return IntersectionResult();
		else
			t = t2;
	else
		if(t2 < 0)
			t = t1;
		else
			t = std::min(t1, t2);

	const Point3D point = ray.Start + t * static_cast<Vector3D>(ray.Vector);

	const NormalizedVector3D n = point - Center;

	return IntersectionResult(point, n);
}

RealColor RT::Sphere::Trace(const RT::Ray &ray, const IntersectionResult& result) const
{
	return RTObject::color * (static_cast<Vector3D>(result.n) * Vector3DByCoords(0, 0, -1));
}
