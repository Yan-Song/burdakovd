#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Utils.h"

// Этот вектор пока не содержит обобщенных координат
template<typename I, int N>
class GenericVector
{
private:
	typedef I dataArray[N];
	dataArray data;
	
public:
	static const int Dimensions = N;

	// конструктор по умолчанию - нули
	inline GenericVector()
	{
		for(int i = 0; i < N; ++i)
			data[i] = 0;
	}

	inline GenericVector(const dataArray& dt)
	{
		for(int i = 0; i < N; ++i)
			data[i] = dt[i];
	}

	inline GenericVector(const GenericVector<I, N>& other)
	{
		for(int i = 0; i < N; ++i)
			data[i] = other[i];
	}

	inline I& operator [](const int index)
	{
		if(index < 0 || index >= N)
			throw new std::out_of_range("Index out of range in I& Vector::operator[]");
		else
			return data[index];
	}

	inline const I& operator [](const int index) const
	{
		if(index < 0 || index >= N)
			throw new std::out_of_range("Index out of range in const I& Vector::operator[]");
		else
			return data[index];
	}

	template<typename J>
	inline operator GenericVector<J, N>() const
	{
		GenericVector<J, N> ans;
		for(int i = 0; i < N; ++i)
			ans[i] = static_cast<J>(data[i]);
		return ans;
	}

	inline GenericVector<I, N> operator +(const GenericVector<I, N>& other) const
	{
		GenericVector<I, N> ans;
		for(int i = 0; i < N; ++i)
			ans[i] = data[i] + other[i];
		return ans;
	}

	inline GenericVector<I, N> operator -(const GenericVector<I, N>& other) const
	{
		GenericVector<I, N> ans;
		for(int i = 0; i < N; ++i)
			ans[i] = data[i] - other[i];
		return ans;
	}

	inline GenericVector<I, N>& operator +=(const GenericVector<I, N>& other)
	{
		for(int i = 0; i < N; ++i)
			data[i] += other[i];
		return *this;
	}

	inline GenericVector<I, N>& operator -=(const GenericVector<I, N>& other)
	{
		for(int i = 0; i < N; ++i)
			data[i] -= other[i];
		return *this;
	}

	inline GenericVector<I, N> operator *(const I k) const
	{
		GenericVector<I, N> ans;
		for(int i = 0; i < N; ++i)
			ans[i] = data[i] * k;
		return ans;
	}

	inline GenericVector<I, N> operator /(const I k) const
	{
		GenericVector<I, N> ans;
		for(int i = 0; i < N; ++i)
			ans[i] = data[i] / k;
		return ans;
	}

	inline GenericVector<I, N>& operator *=(const I k)
	{
		for(int i = 0; i < N; ++i)
			data[i] *= k;
	}

	inline GenericVector<I, N>& operator /=(const I k)
	{
		for(int i = 0; i < N; ++i)
			data[i] /= k;
	}

	// унарный минус
	inline GenericVector<I, N> operator -() const
	{
		GenericVector<I, N> ans;
		for(int i = 0; i < N; ++i)
			ans[i] = - data[i];
		return ans;
	}

	// Длина вектора
	inline double Length() const
	{
		double s = 0;
		for(int i = 0; i < N; ++i)
			s += sqr(static_cast<double>(data[i]));
		return sqrt(s);
	}

	// Расстояние между точками
	inline double Distance(const GenericVector<I, N>& other)
	{
		return (other - *this).Length();
	}
};

template<typename I, int N>
inline GenericVector<I, N> operator *(const I k, const GenericVector<I, N>& v)
{
	return v * k;
}

// евклидово скалярное произведение (попарное произведение соответствующих координат)
template<typename I, int N>
inline GenericVector<I, N> operator *(const GenericVector<I, N>& A, const GenericVector<I, N>& B)
{
	GenericVector<I, N> C;

	for(int i = 0; i < N; ++i)
		C[i] = A[i] * B[i];

	return C;
}

// евклидово скалярное произведение (попарное произведение соответствующих координат)
template<typename I, int N>
inline GenericVector<I, N> operator *=(GenericVector<I, N>& A, const GenericVector<I, N>& B)
{
	for(int i = 0; i < N; ++i)
		A[i] *= B[i];

	return A;
}

// z-координата векторного произведения двумерных векторов, лежащих в плоскости XY
// вычисляется как будто это трёхмерные вектора, с нулевой третьей координатой
template<typename I>
inline I operator ^(const GenericVector<I, 2>& A, const GenericVector<I, 2>& B)
{
	return A[0] * B[1] - A[1] * B[0];
}

// вектор на плоскости, координаты - double
typedef GenericVector<double, 2> Vector2D;

// точка на плоскости, координаты - double
typedef Vector2D Point2D;

// "Точка на экране", координаты - int, работает быстрее чем Vector2D, рекомендуется к использованию если дробные координаты не нужны.
typedef GenericVector<int, 2> ScreenPoint;

// а вот это ппц, так как я хз как сделать удобный конструктор с N параметрами
Vector2D Vector2DByCoords(double x, double y);

ScreenPoint ScreenPointByCoords(int x, int y);

// вектор, соответствующий началу координат
const Vector2D Vector00 = Vector2DByCoords(0.0, 0.0);

// x = 1.0, y = 1.0
const Vector2D Vector11 = Vector2DByCoords(1.0, 1.0);

#endif
