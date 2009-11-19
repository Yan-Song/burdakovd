#ifndef LIGHT_H
#define LIGHT_H

#include <sdlapplication/Color.h>
#include <sdlapplication/Vector.h>
#include "IntersectionResult.h"
#include "RTObject.h"

namespace RT
{
	class ILight
	{
	public:
		virtual Point3D Position() const = 0;
		virtual RealColor Color() const = 0;

		virtual ~ILight() {}
	};

	class Light : public IObject3D, public ILight
	{
	private:
		Vector3D _Position;
		RealColor _Color;

	public:
		Light(const Vector3D& Position, const RealColor& Color) : _Position(Position), _Color(Color)
		{
		}

		// ILight members
		virtual Point3D Position() const
		{
			return _Position;
		}

		virtual RealColor Color() const
		{
			return _Color;
		}

		// IObject3D members
		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi)
		{
			_Position = Affine::Rotate3D(axe, phi, base) * _Position;
		}

		virtual void Move(const Vector3D& offset)
		{
			_Position += offset;
		}
	};
}

#endif
