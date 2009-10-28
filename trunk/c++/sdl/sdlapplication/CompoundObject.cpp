#include "CompoundObject.h"

void CompoundObject::Add(GraphObject2D* const object)
{
	objects.push_back(object);
}

void CompoundObject::Draw(const SDLApplication *app, const Vector& base) const
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Draw(app, base + Center);
}
