#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include <stdexcept>

#define sqr(x) ((x) * (x))
#define mset(x, value) memset(x, value, sizeof(x))

// ���� ������ ���� �� �������� ���������� ���������
template<typename I, int N>
class GenericVector
{
private:
	typedef I dataArray[N];
	dataArray data;
	
public:
	static const int Dimensions = N;

	// ����������� �� ���������
	GenericVector()
	{
		for(int i = 0; i < N; ++i)
			data[i] = 0;
	}

	GenericVector(const dataArray& dt)
	{
		for(int i = 0; i < N; ++i)
			data[i] = dt[i];
	}

	GenericVector(const GenericVector<I, N>& other)
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
			ans[i] += other[i];
		return *this;
	}

	inline GenericVector<I, N>& operator -=(const GenericVector<I, N>& other)
	{
		for(int i = 0; i < N; ++i)
			ans[i] -= other[i];
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

	// ������� �����
	inline GenericVector<I, N> operator -() const
	{
		GenericVector<I, N> ans;
		for(int i = 0; i < N; ++i)
			ans[i] = - data[i];
		return ans;
	}

	// ����� �������
	inline double Length() const
	{
		double s = 0;
		for(int i = 0; i < N; ++i)
			s += sqr(static_cast<double>(data[i]));
		return sqrt(s);
	}

	// ���������� ����� �������
	inline double Distance(const GenericVector<I, N>& other)
	{
		return (other - *this).Length();
	}
};

// ������ �� ���������, ���������� - double
typedef GenericVector<double, 2> Vector2D;

// ����� �� ���������, ���������� - double
typedef Vector2D Point2D;

// "����� �� ������", ���������� - int, �������� ������� ��� Vector2D, ������������� � ������������� ���� ������� ���������� �� �����.
typedef GenericVector<int, 2> ScreenPoint;

// � ��� ��� ���, ��� ��� � �� ��� ������� ������� ����������� � N �����������
Vector2D Vector2DByCoords(double x, double y);

ScreenPoint ScreenPointByCoords(int x, int y);

#endif
