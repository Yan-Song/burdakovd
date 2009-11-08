#ifndef NORMALIZEDVECTOR3D_H
#define NORMALIZEDVECTOR3D_H

#include "Vector.h"

namespace RT
{
	// нормированный вектор, который гарантирует, что его длина равна 1.0
	// ну и вследствии этого доступ к его компонентам только на чтение
	class NormalizedVector3D
	{
	private:
		double data[3];

	public:
		// в всех своих конструкторах вектор нормируется
		NormalizedVector3D(const double x, const double y, const double z);

		NormalizedVector3D(const Vector3D& vector);

		inline operator Vector3D() const
		{
			return Vector3D(data);
		}

		inline double operator[](const int index) const
		{
			if(index < 0 || index >= 3)
				throw new std::out_of_range("Index out of range in NormalizedVector::operator[]");
			else
				return data[index];
		}

		inline double Distance(const Vector3D& other) const
		{
			return (static_cast<Vector3D>(*this) - other).Length();
		}

		inline double x() const { return data[0]; }

		inline double y() const { return data[1]; }

		inline double z() const { return data[2]; }
	};
}

#endif
