#ifndef COMPOUNDOBJECT_H
#define COMPOUNDOBJECT_H

#include "RTObject.h"
#include <vector>

namespace RT
{
	class CompoundObject : public IRTObject
	{
	protected:
		typedef std::vector<IRTObject*> ObjectList;
		ObjectList objects;

	public:
		// переданный объект будет уничтожен в деструкторе
		virtual void Add(IRTObject* object);

		virtual bool PossibleIntersection(const Ray& ray) const;

		virtual MaybeIntersection FindIntersection(const Ray& ray) const;

		virtual RealColor Trace(const Ray& ray, const Intersection& intersection) const;

		virtual ~CompoundObject();
	};
}

#endif
