#ifndef PROJECTION_H
#define PROJECTION_H

#include "Matrix.h"
#include "Vector.h"
#include "Utils.h"
#include "GraphObject.h"
#include "Affine.h"

namespace Projection
{
	typedef GenericMatrix<4> Matrix;

	// ортографическа€ проекци€ вдоль заданной оси (K) с заданным смещением
	template<int K>
	Matrix GenericOrhographicProjection()
	{
		assert(K >= 0 && K < 3);

		Matrix ans(1.0);
		ans[K][K] = 0;

		return ans;
	}

	inline Matrix OrthographicXProjection() { return GenericOrhographicProjection<0>(); }

	inline Matrix OrthographicYProjection() { return GenericOrhographicProjection<1>(); }

	inline Matrix OrthographicZProjection() { return GenericOrhographicProjection<2>(); }

	template<int I, int J>
	inline Vector2D GetSomeCoords(const Vector3D& v)
	{
		assert(I >= 0 && I < 3 && J >= 0 && J < 3 && I != J);
		return Vector2DByCoords(v[I], v[J]);
	}

	inline Vector2D GetXY(const Vector3D& v) { return GetSomeCoords<0, 1>(v); }

	inline Vector2D GetXZ(const Vector3D& v) { return GetSomeCoords<0, 2>(v); }
	
	// матрица перспективного преобразовани€ (без проектировани€), вдоль оси с номером K
	// наблюдатель находитс€ в точке position, картинна€ плоскость - это плоскость x[K] = xK
	template<int K>
	Matrix PerspectiveProjection(Vector3D position, const double xK = 0)
	{
		assert(K >= 0 && K < 3);

		// —тандартна€ матрица из Ѕорескова
		Matrix m(1.0);
		m[3][K] = - 1 / (position[K] - xK);

		// ¬ Ѕорескове наблюдатель находилс€ на оси, чтоб обобщить ситуацию домножим матрицу на матрицы смещени€
		position[K] = xK;

		return Affine::Move(position) * m * Affine::Move(-position);
	}

	// ѕерспективна€ проекци€ вдоль оси Y, на плоскость XZ.
	// ѕри условии, что наблюдатель находитс€ в точке position
	// предполагаетс€ что Y координата наблюдател€ отрицательна
	// (направление координат X - вправо, Y - вперЄд сквозь экран, Z - вверх)
	class PerspectiveProjector : public IProjector
	{
	private:
		Matrix m;

	public:
		PerspectiveProjector(const Vector3D& position) : m(PerspectiveProjection<1>(position, 0)) {}

		virtual ScreenPoint projection(const Vector3D& point) const
		{
			return GetXZ(m * point);
		}
	};
}

#endif
