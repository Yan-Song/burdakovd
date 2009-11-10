#ifndef COMPOUNDOBJECT_H
#define COMPOUNDOBJECT_H

#include "RTObject.h"
#include <vector>
#include "Shared.h"

namespace RT
{
	class CompoundObject : public IRTObject
	{
	public:
		typedef shared_ptr<IRTObject> SharedObject;

	protected:
		typedef std::vector<SharedObject> ObjectList;
		ObjectList objects;

	public:
		virtual void Add(const SharedObject& object);

		virtual bool PossibleIntersection(const Ray& ray) const;

		virtual MaybeIntersection FindIntersection(const Ray& ray) const;

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi);

		virtual void Move(const Vector3D& offset);
	};
}

#endif
