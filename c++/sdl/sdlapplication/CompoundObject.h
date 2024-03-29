#ifndef COMPOUNDOBJECT_H
#define COMPOUNDOBJECT_H

#include "GraphObject.h"
#include "SDLApplication.h"
#include "Vector.h"
#include <list>

// составной графический объект
class CompoundObject2D : public GraphObject2D
{
protected:
	typedef std::list<GraphObject2D*> ObjectList;

	ObjectList objects;
	
	// добавить объект
	// объект, указатель на который передан, будет удалён в деструкторе, вызывыющая сторона не должна этим заниматься
	void Add(GraphObject2D* const object);

public:
	virtual void Draw(SDLApplication* const app, const Vector& base) const;

	virtual void Rotate(const double phi);

	virtual void Scale(const Vector2D& coefficients);

	virtual ~CompoundObject2D();
};

class CompoundObject3D : public GraphObject3D
{
protected:
	typedef std::list<GraphObject3D*> ObjectList;

	ObjectList objects;

public:
	CompoundObject3D() : objects() {}

	// добавить объект
	// объект, указатель на который передан, будет удалён в деструкторе, вызывыющая сторона не должна этим заниматься
	void Add(GraphObject3D* const object);

	virtual void Scale(const Vector3D& coefficients);

	virtual void Draw(const Vector3D& base, ITriangleDrawer* const drawer) const;

	virtual void Rotate(const Affine::Axe axe, const double phi);

	virtual ~CompoundObject3D();
};

#endif
