#include "Geometry2D.h"
#include "Vector.h"

bool Geometry2D::hasIntersection(const Point2D& A, const Point2D& B,  const Point2D& C, const Point2D& D)
{
	// Отрезки имеют пересечение, если 
	// 1) A и B по разные стороны от CD
	// 2) C и D по разные стороны от AB

	Vector2D AB = B - A, AC = C - A, AD = D - A, CA = A - C, CB = B - C, CD = D - C;

	// если следующие две строки кода непонятны, то нарисуйте два пересекающихся отрезка и читайте камменты
	// A и B по разные стороны от CD <=>
	// кратчайший поворот от CD к CB и от CD к CA - в разных направлениях <=>
	// по определению векторного произведения: CD ^ CB и CD ^ CA имеют Z координаты противоположного знака <=>
	// при их умножении получим отрицательное число
	bool first = VectorMultiplication2D(CD, CB) * VectorMultiplication2D(CD, CA) < 0;

	bool second = VectorMultiplication2D(AB, AC) * VectorMultiplication2D(AB, AD) < 0;

	return first && second;
}

struct Line2D
{
	Vector2D P, D;
	// уравнение прямой на плоскости: (x, y) = P + t * D; t <- R

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
		// если отрезки пересекаются, то можно рассматривать пересечение содержащих их прямых
		Line2D first(A, B), second(C, D);

		return first * second;
	}
	else
	{
		throw std::invalid_argument("this segments have not intersection");
	}
}
