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

	// ��������������� �������� ����� �������� ��� (K) � �������� ���������
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
	
	// ������� �������������� �������������� (��� ��������������), ����� ��� � ������� K
	// ����������� ��������� � ����� position, ��������� ��������� - ��� ��������� x[K] = xK
	template<int K>
	Matrix PerspectiveProjection(Vector3D position, const double xK = 0)
	{
		assert(K >= 0 && K < 3);

		// ����������� ������� �� ���������
		Matrix m(1.0);
		m[3][K] = - 1 / (position[K] - xK);

		// � ��������� ����������� ��������� �� ���, ���� �������� �������� �������� ������� �� ������� ��������
		position[K] = xK;

		return Affine::Move(position) * m * Affine::Move(-position);
	}

	// ������������� �������� ����� ��� Y, �� ��������� XZ.
	// ��� �������, ��� ����������� ��������� � ����� position
	// �������������� ��� Y ���������� ����������� ������������
	// (����������� ��������� X - ������, Y - ����� ������ �����, Z - �����)
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
