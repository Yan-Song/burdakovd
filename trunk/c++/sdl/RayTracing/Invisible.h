#ifndef INVISIBLE_H
#define INVISIBLE_H

#include <sdlapplication/Shared.h>
#include "RTObject.h"

namespace RT
{
	// "невидимый" RTObject
	class Invisible : public IRTObject 
	{
	private:
		Shared::shared_ptr<IObject3D> _object;

	public:
		Invisible(const Shared::shared_ptr<IObject3D> object) : _object(object) {}

		virtual bool PossibleIntersection(const RT::Ray& ) const
		{
			return false;
		}

		virtual MaybeIntersection FindIntersection(const RT::Ray& ) const
		{
			return NoIntersection();
		}

		virtual void Move(const Vector3D& offset)
		{
			_object->Move(offset);
		}

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi)
		{
			_object->Rotate(axe, base, phi);
		}
	};
}

#endif
