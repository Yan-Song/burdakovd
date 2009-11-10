#ifndef AFFINE_H
#define AFFINE_H

#include "Matrix.h"
#include "Vector.h"

namespace Affine
{
	// Матрица параллельного переноса, не зависит от размерности, поэтому шаблон
	template<int N>
	GenericMatrix<N+1> Move(const GenericVector<double, N>& v)
	{
		GenericMatrix<N+1> ans(1.0); // единичная матрица

		for(int i = 0; i < N; ++i)
			ans[i][N] = v[i];

		return ans;
	}

	// Матрица вращения, пока только для 2D
	GenericMatrix<3> Rotate2D(const double phi, const Vector2D& center = Vector00);

	// Матрица растяжения, только вдоль осей координат, для любых размерностей
	template<int N>
	GenericMatrix<N+1> Scale(const GenericVector<double, N>& coefficients)
	{
		GenericMatrix<N+1> m;

		for(int i = 0; i < N; ++i)
			m[i][i] = coefficients[i];

		m[N][N] = 1.0;

		return m;
	}

	// матрица растяжения относительно заданного центра
	template<int N>
	inline GenericMatrix<N+1> Scale(const GenericVector<double, N>& coefficients, const GenericVector<double, N>& center)
	{
		return Move(center) * Scale(coefficients) * Move(-center);
	}

	// Flip() - отражение - частный случай растяжения с коэффициентом -1

	enum Axe
	{
		X = 0,
		Y = 1,
		Z = 2
	};

	// Матрица вращения вокруг заданной оси
	GenericMatrix<4> Rotate3D(const Axe axe, const double phi, const Vector3D& center = Vector000);
};

#endif
