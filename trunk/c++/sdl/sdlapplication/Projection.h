#ifndef PROJECTION_H
#define PROJECTION_H

#include "Matrix.h"
#include "Vector.h"
#include "Utils.h"

namespace Projection
{
	typedef GenericMatrix<4> Matrix;

	// ортографическая проекция вдоль заданной оси (K) с заданным смещением
	template<int K>
	Matrix GenericOrhographicProjection(const double offset = 0.0)
	{
		assert(K >= 0 && K < 3);

		Matrix ans(1.0);
		ans[K][K] = 0;
		ans[K][3] = offset;

		return ans;
	}

	inline Matrix OrthographicXProjection(const double offset = 0) { return GenericOrhographicProjection<0>(offset); }

	inline Matrix OrthographicYProjection(const double offset = 0) { return GenericOrhographicProjection<1>(offset); }

	inline Matrix OrthographicZProjection(const double offset = 0) { return GenericOrhographicProjection<2>(offset); }

	template<int I, int J>
	inline Vector2D GetSomeCoords(const Vector3D& v)
	{
		assert(I >= 0 && I < 3 && J >= 0 && J < 3 && I != J);
		return Vector2DByCoords(v[I], v[J]);
	}

	inline Vector2D GetXY(const Vector3D& v) { return GetSomeCoords<0, 1>(v); }

	inline Vector2D GetXZ(const Vector3D& v) { return GetSomeCoords<0, 2>(v); }
	
}

#endif
