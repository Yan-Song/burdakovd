#include "Cube.h"
#include "Polygon.h"
#include "Color.h"
#include "Vector.h"
#include "CompoundObject.h"

Polygon3D* MakePolygon(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Color& color)
{
	Polygon3D* p = new Polygon3D(color);

	p->Add(a);
	p->Add(b);
	p->Add(c);
	p->Add(d);

	return p;
}

Cube::Cube(const Vector3D &center, const double edgeLength, const Color &color)
{
	// ������� ������ ����������� ��������� �����, ����� ������������ � ���������� ��� ���� ����

	// ����������� ������� (�����: ������ ���������, �����: 2)
	const Point3D& A = Vector3DByCoords(-1, -1, -1);
	const Point3D& B = Vector3DByCoords(-1, +1, -1);
	const Point3D& C = Vector3DByCoords(+1, +1, -1);
	const Point3D& D = Vector3DByCoords(+1, -1, -1);

	const Point3D& E = Vector3DByCoords(-1, -1, +1);
	const Point3D& F = Vector3DByCoords(-1, +1, +1);
	const Point3D& G = Vector3DByCoords(+1, +1, +1);
	const Point3D& H = Vector3DByCoords(+1, -1, +1);

	// ��������� �����, ������� ������ ����� ����������� ������ ������� �������, ���� �������� �����
	Add(MakePolygon(A, B, C, D, color)); // ������
	Add(MakePolygon(E, H, G, F, color)); // �������

	Add(MakePolygon(A, D, H, E, color));
	Add(MakePolygon(D, C, G, H, color));
	Add(MakePolygon(C, B, F, G, color));
	Add(MakePolygon(A, E, F, B, color));

	// ����������� ��� ��������, ������������
	Scale(Vector111 * edgeLength / 2);

	// ��������� ��� � �������� �����
	Move(center);	
}
