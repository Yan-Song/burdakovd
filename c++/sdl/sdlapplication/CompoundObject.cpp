#include "CompoundObject.h"

void CompoundObject::Add(GraphObject2D* const object)
{
	objects.push_back(object);
}

void CompoundObject::Draw(const SDLApplication *app) const
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Draw(app);
}

void CompoundObject::Shift(const Vector2D &v)
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Shift(v);
}
