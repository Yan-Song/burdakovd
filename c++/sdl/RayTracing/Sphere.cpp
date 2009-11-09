#include "Sphere.h"
#include "sdlapplication/Vector.h"
#include "Polynom.h"
#include "SquareEquation.h"

bool RT::Sphere::PossibleIntersection(const RT::Ray &ray) const
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

RT::MaybeIntersection RT::Sphere::FindIntersection(const RT::Ray &ray) const
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
		return NoIntersection();
	}

	double t;

	// �������� ��������� ����� �����������, �� � ������������� t
	// ������������� t - ��� �� ������������ ��� ����������
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

	const Point3D point = ray.Start + t * static_cast<Vector3D>(ray.Vector);

	const NormalizedVector3D n = point - Center;

	return Intersection(point, n);
}

RealColor RT::Sphere::Trace(const RT::Ray &ray, const Intersection& intersection) const
{
	return RTObject::color * (static_cast<Vector3D>(intersection.n) * Vector3DByCoords(0, 0, -1));
}
