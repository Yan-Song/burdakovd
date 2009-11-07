#include "Geometry2D.h"
#include "Vector.h"

bool Geometry2D::hasIntersection(const Point2D& A, const Point2D& B,  const Point2D& C, const Point2D& D)
{
	// ������� ����� �����������, ���� 
	// 1) A � B �� ������ ������� �� CD
	// 2) C � D �� ������ ������� �� AB

	Vector2D AB = B - A, AC = C - A, AD = D - A, CA = A - C, CB = B - C, CD = D - C;

	// ���� ��������� ��� ������ ���� ���������, �� ��������� ��� �������������� ������� � ������� ��������
	// A � B �� ������ ������� �� CD <=>
	// ���������� ������� �� CD � CB � �� CD � CA - � ������ ������������ <=>
	// �� ����������� ���������� ������������: CD ^ CB � CD ^ CA ����� Z ���������� ���������������� ����� <=>
	// ��� �� ��������� ������� ������������� �����
	bool first = VectorMultiplication2D(CD, CB) * VectorMultiplication2D(CD, CA) < 0;

	bool second = VectorMultiplication2D(AB, AC) * VectorMultiplication2D(AB, AD) < 0;

	return first && second;
}

struct Line2D
{
	Vector2D P, D;
	// ��������� ������ �� ���������: (x, y) = P + t * D; t <- R

	Line2D(const Point2D& A, const Point2D& B) : P(A), D(B - A)
	{
	}
};

Point2D operator *(const Line2D& first, const Line2D& second)
{
	double t1 = VectorMultiplication2D(second.P - first.P, second.D) / VectorMultiplication2D(first.D, second.D);

	return first.P + t1 * first.D;
}

Point2D Geometry2D::Intersection(const Point2D& A, const Point2D& B,  const Point2D& C, const Point2D& D)
{
	if(Geometry2D::hasIntersection(A, B, C, D))
	{
		// ���� ������� ������������, �� ����� ������������� ����������� ���������� �� ������
		Line2D first(A, B), second(C, D);

		return first * second;
	}
	else
	{
		throw new std::invalid_argument("this segments have not intersection");
	}
}
