#include "Cube.h"
#include "Polygon.h"
#include "Color.h"
#include "Vector.h"
#include "CompoundObject.h"
#include "Tetragon.h"

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
	Add(new Tetragon(A, B, C, D, color)); // ������
	Add(new Tetragon(E, H, G, F, color)); // �������

	Add(new Tetragon(A, D, H, E, color));
	Add(new Tetragon(D, C, G, H, color));
	Add(new Tetragon(C, B, F, G, color));
	Add(new Tetragon(A, E, F, B, color));

	// ����������� ��� ��������, ������������
	Scale(Vector111 * edgeLength * 0.5);

	// ��������� ��� � �������� �����
	Move(center);	
}
