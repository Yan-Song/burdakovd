#ifndef PROJECTION_H
#define PROJECTION_H

#include "Matrix.h"
#include "Vector.h"
#include "Utils.h"
#include "Interfaces.h"
#include "Affine.h"

namespace Projection
{
	typedef GenericMatrix<4> Matrix;

	template<int I, int J>
	inline Vector2D GetSomeCoords(const Vector3D& v)
	{
		assert(I >= 0 && I < 3 && J >= 0 && J < 3 && I != J);
		return Vector2DByCoords(v[I], v[J]);
	}

	inline Vector2D GetXY(const Vector3D& v) { return GetSomeCoords<0, 1>(v); }

	inline Vector2D GetXZ(const Vector3D& v) { return GetSomeCoords<0, 2>(v); }
	
	// матрица перспективного преобразования (без проектирования), вдоль оси с номером K
	// наблюдатель находится в точке position, картинная плоскость - это плоскость x[K] = xK
	template<int K>
	Matrix PerspectiveProjection(Vector3D position, const double xK = 0)
	{
		assert(K >= 0 && K < 3);

		// Стандартная матрица из Борескова
		Matrix m(1.0);
		m[3][K] = - 1 / (position[K] - xK);

		// В Борескове наблюдатель находился на оси, чтоб обобщить ситуацию домножим матрицу на матрицы смещения
		position[K] = xK;

		return Affine::Move(position) * m * Affine::Move(-position);
	}
}

#endif
