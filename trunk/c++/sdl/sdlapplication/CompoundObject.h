#ifndef COMPOUNDOBJECT_H
#define COMPOUNDOBJECT_H

#include "GraphObject.h"
#include "SDLApplication.h"
#include "Vector.h"
#include <list>

// составной графический объект
class CompoundObject : public GraphObject2D
{
protected:
	typedef std::list<GraphObject2D*> ObjectList;

	ObjectList objects;
	
	// добавить объект
	// объект, указатель на который передан, будет удалён в деструкторе, вызывыющая сторона не должна этим заниматься
	void Add(GraphObject2D* const object);

public:
	virtual void Draw(const SDLApplication* app, const Vector& base) const;

	virtual void Rotate(const double phi);

	virtual void Scale(const Vector2D& coefficients);
};

#endif
