#ifndef SCENE_H
#define SCENE_H

#include "SDLApplication.h"
#include "CompoundObject.h"
#include "GraphObject.h"

class Scene2D : public CompoundObject2D
{
public:
	// �������� ������
	// ������, ��������� �� ������� �������, ����� ����� � �����������, ���������� ������� �� ������ ���� ����������
	inline void Add(GraphObject2D* const object)
	{
		CompoundObject2D::Add(object);
	}
};

class Scene3D : public CompoundObject3D
{
public:
	inline void Add(GraphObject3D* const object)
	{
		CompoundObject3D::Add(object);
	}
};

#endif
