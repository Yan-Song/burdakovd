#ifndef SCENE_H
#define SCENE_H

#include "SDLApplication.h"
#include "CompoundObject.h"
#include "GraphObject.h"

class Scene : public CompoundObject
{
public:
	// добавить объект
	// объект, указатель на который передан, будет удалён в деструкторе, вызывыющая сторона не должна этим заниматься
	inline void Add(GraphObject2D* const object)
	{
		CompoundObject::Add(object);
	}
};

#endif
