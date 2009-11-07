#include "Triangle3D.h"
#include "Affine.h"
#include "Matrix.h"
#include <algorithm>

void Triangle3D::Scale(const Vector3D& coefficients)
{
	A = zipWithMultiplication(A, coefficients);
	B = zipWithMultiplication(B, coefficients);
	C = zipWithMultiplication(C, coefficients);

	// ! � ��� ���!
	// ����� ����� ���������� ������������� ������� ������ ������
	// �� ��� ������ ��������� ������� ������ ������ ����� ������
	// ������ ����� ������� ������, �� ����� �������� ������ ��-�� �����
	// ��������� �� - ��� ������������� ����������� ��� ����������
	// �� ���� ����������� ��� ������������ � ������� �� ����
	if(coefficients[0] * coefficients[1] * coefficients[2] < 0)
		std::swap(B, C);
}

void Triangle3D::Draw(const Vector3D &base, ITriangleDrawer * const drawer) const
{
	drawer->DrawTriangle(base + Center + A, base + Center + B, base + Center + C, color);
}

void Triangle3D::Rotate(const int axe, const double phi)
{
	GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi);

	A = rotator * A;
	B = rotator * B;
	C = rotator * C;
}
