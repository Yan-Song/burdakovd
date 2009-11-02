#ifndef AFFINE_H
#define AFFINE_H

#include "Matrix.h"
#include "Vector.h"

namespace Affine
{
	// ������� ������������� ��������, �� ������� �� �����������, ������� ������
	template<int N>
	GenericMatrix<N+1> Move(const GenericVector<double, N>& v)
	{
		GenericMatrix<N+1> ans(1.0); // ��������� �������

		for(int i = 0; i < N; ++i)
			ans[i][N] = v[i];

		return ans;
	}

	// ������� ��������, ���� ������ ��� 2D
	GenericMatrix<3> Rotate2D(const double phi, const Vector2D& center = Vector00);

	// ������� ����������, ������ ����� ���� ���������, ��� ����� ������������
	template<int N>
	GenericMatrix<N+1> Scale(const GenericVector<double, N>& coefficients)
	{
		GenericMatrix<N+1> m;

		for(int i = 0; i < N; ++i)
			m[i][i] = coefficients[i];

		m[N][N] = 1.0;

		return m;
	}

	// ������� ��������� ������������ ��������� ������
	template<int N>
	inline GenericMatrix<N+1> Scale(const GenericVector<double, N>& coefficients, const GenericVector<double, N>& center)
	{
		return Move(center) * Scale(coefficients) * Move(-center);
	}

	// Flip() - ��������� - ������� ������ ���������� � ������������� -1
};

#endif
