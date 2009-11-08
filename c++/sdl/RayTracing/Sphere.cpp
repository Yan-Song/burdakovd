#include "Sphere.h"
#include "Vector.h"

bool RT::Sphere::CheckIntersection(const RT::Ray &ray) const
{
	const Vector3D SC = Center - ray.Start;
	const Vector3D v = ray.Vector;
	const double distance = (v ^ SC).Length();

	// ��� ������������ �� ������, ����
	// 1) ���������� �� ������ �� ���� <= R (�� ���� ������ ����������� �� ������) �
	// 2) ������ ��������� � ������� ����� ���� 3) ��������� ����� ������ �����
	return (distance <= R) && ((v * SC > 0) || (Center.Distance(ray.Start) < R));
}
