#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "Utils.h"

template<typename I, int N>
class GenericVector
{
protected:
	typedef I dataArray[N];
	dataArray data;

public:
	static const int Dimensions = N;

public:
	GenericVector(const bool initialize = false, const I& value = 0)
	{
		if(initialize)
			std::fill_n(data, N, value);
	}

	inline GenericVector(const dataArray& dt)
	{
		for(int i = 0; i < N; ++i)
			data[i] = dt[i];
	}

	inline I& operator [](const int index)
	{
		#ifndef NDEBUG
		if(index < 0 || index >= N)
			throw std::out_of_range("Index out of range in I& Vector::operator[]");
		#endif
		return data[index];
	}

	inline const I& operator [](const int index) const
	{
		#ifndef NDEBUG
		if(index < 0 || index >= N)
			throw std::out_of_range("Index out of range in const I& Vector::operator[]");
		#endif

		return data[index];
	}

	template<typename J>
	inline operator GenericVector<J, N>() const
	{
		GenericVector<J, N> ans(false);

		for(int i = 0; i < N; ++i)
			ans[i] = static_cast<J>(data[i]);

		return ans;
	}

	// Длина вектора
	inline I QLength() const
	{
		I s = static_cast<I>(0);

		for(int i = 0; i < N; ++i)
			s += sqr(data[i]);

		return s;
	}

	inline double Length() const
	{
		return sqrt(QLength());
	}

	// Расстояние между точками
	inline double Distance(const GenericVector<I, N>& other) const
	{
		return (other - *this).Length();
	}

	inline I QDistance(const GenericVector<I, N>& other) const
	{
		return (other - *this).QLength();
	}
};


// вектор на плоскости, координаты - double
typedef GenericVector<double, 2> Vector2D;

// точка на плоскости, координаты - double
typedef Vector2D Point2D;

// "Точка на экране", координаты - int, работает быстрее чем Vector2D, рекомендуется к использованию если дробные координаты не нужны.
typedef GenericVector<int, 2> ScreenPoint;

// вектор в трёхмерном пространстве, координаты - double
typedef GenericVector<double, 3> Vector3D;
typedef Vector3D Point3D;

// а вот это ппц, так как я хз как сделать удобный конструктор с N параметрами
Vector2D Vector2DByCoords(const double x, const double y);
Vector3D Vector3DByCoords(const double x, const double y, const double zs);

ScreenPoint ScreenPointByCoords(const int x, const int y);

// вектор, соответствующий началу координат
const Vector2D Vector00(true, 0.0);
const Vector3D Vector000(true, 0.0);

// x = 1.0, y = 1.0
const Vector2D Vector11(true, 1.0);
const Vector3D Vector111(true, 1.0);

// простейшие операции

template<typename I, int N>
inline GenericVector<I, N> operator +(const GenericVector<I, N>& first, const GenericVector<I, N>& other)
{
	GenericVector<I, N> ans(first);

	for(int i = 0; i < N; ++i)
		ans[i] += other[i];

	return ans;
}

template<typename I, int N>
inline GenericVector<I, N> operator -(const GenericVector<I, N>& first, const GenericVector<I, N>& other)
{
	GenericVector<I, N> ans(first);

	for(int i = 0; i < N; ++i)
		ans[i] -= other[i];

	return ans;
}

template<typename I, int N>
inline GenericVector<I, N>& operator +=(GenericVector<I, N>& first, const GenericVector<I, N>& other)
{
	for(int i = 0; i < N; ++i)
		first[i] += other[i];

	return first;
}

template<typename I, int N>
inline GenericVector<I, N>& operator -=(GenericVector<I, N>& first, const GenericVector<I, N>& other)
{
	for(int i = 0; i < N; ++i)
		first[i] -= other[i];

	return first;
}

template<typename I, int N>
inline GenericVector<I, N> operator *(const GenericVector<I, N>& first, const I k)
{
	GenericVector<I, N> ans(first);

	for(int i = 0; i < N; ++i)
		ans[i] *= k;

	return ans;
}

template<typename I, int N>
inline GenericVector<I, N> operator *(const I k, const GenericVector<I, N>& v)
{
	return v * k;
}

template<typename I, int N>
inline GenericVector<I, N> operator /(const GenericVector<I, N>& first, const I k)
{
	GenericVector<I, N> ans(first);

	for(int i = 0; i < N; ++i)
		ans[i] /= k;

	return ans;
}

template<typename I, int N>
inline GenericVector<I, N>& operator *=(GenericVector<I, N>& first, const I k)
{
	for(int i = 0; i < N; ++i)
		first[i] *= k;

	return first;
}

template<typename I, int N>
inline GenericVector<I, N>& operator /=(GenericVector<I, N>& first, const I k)
{
	for(int i = 0; i < N; ++i)
		first[i] /= k;

	return first;
}

// унарный минус
template<typename I, int N>
inline GenericVector<I, N> operator -(const GenericVector<I, N>& first)
{
	GenericVector<I, N> ans(false);

	for(int i = 0; i < N; ++i)
		ans[i] = -first[i];

	return ans;
}

// попарное произведение координат
template<typename I, int N>
inline GenericVector<I, N> zipWithMultiplication(const GenericVector<I, N>& A, const GenericVector<I, N>& B)
{
	GenericVector<I, N> C(A);

	for(int i = 0; i < N; ++i)
		C[i] *= B[i];

	return C;
}

// евклидово скалярное произведение (сумма попарных произведений соответствующих координат)
template<typename I, int N>
inline I operator *(const GenericVector<I, N>& A, const GenericVector<I, N>& B)
{
	I ans = static_cast<I>(0);

	for(int i = 0; i < N; ++i)
		ans += A[i] * B[i];

	return ans;
}

// векторное произведение трёхмерных векторов
template<typename I>
inline GenericVector<I, 3> operator ^(const GenericVector<I, 3>& A, const GenericVector<I, 3>& B)
{
	GenericVector<I, 3> ans(false);

	ans[0] = A[1] * B[2] - A[2] * B[1];
	ans[1] = A[2] * B[0] - A[0] * B[2];
	ans[2] = A[0] * B[1] - A[1] * B[0];

	return ans;
}

// "упрощенное" векторное произведение для двумерных векторов
// (дополнить их нулевой третьей координатой, перемножить, а затем вернуть третью координату произведения (остальные две нули))
// вообще это не настоящее векторное произведение, поэтому я его не обозначил значком ^
template<typename I>
inline I VectorMultiplication2D(const GenericVector<I, 2>& A, const GenericVector<I, 2>& B)
{
	GenericVector<I, 3> a(false);
	GenericVector<I, 3> b(false);

	for(int i = 0; i < 2; ++i)
	{
		a[i] = A[i];
		b[i] = B[i];
	}
	a[2] = 0;
	b[2] = 0;

	return (a ^ b)[2];
}

template<typename I>
inline GenericVector<I, 3> operator ^=(GenericVector<I, 3>& A, const GenericVector<I, 3>& B)
{
	A = A ^ B;
	return A;
}

template<typename I, int N>
inline std::ostream& operator <<(std::ostream& os, const GenericVector<I, N>& v)
{
	for(int i = 0; i < N; ++i)
		os << (i == 0 ? "(" : "; ") << v[i];
	os << ")";
	return os;
}

#endif
