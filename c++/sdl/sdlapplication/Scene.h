#ifndef SCENE_H
#define SCENE_H

#include "SDLApplication.h"
#include "CompoundObject.h"
#include "GraphObject.h"

class Scene : public CompoundObject
{
public:
	// �������� ������
	// ������, ��������� �� ������� �������, ����� ����� � �����������, ���������� ������� �� ������ ���� ����������
	inline void Add(GraphObject2D* const object)
	{
		CompoundObject::Add(object);
	}
};

#endif
