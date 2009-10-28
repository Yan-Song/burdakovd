#ifndef COMPOUNDOBJECT_H
#define COMPOUNDOBJECT_H

#include "GraphObject.h"
#include "SDLApplication.h"
#include "Vector.h"
#include <list>

// ��������� ����������� ������
class CompoundObject : public GraphObject2D
{
private:
	typedef std::list<GraphObject2D*> ObjectList;
	ObjectList objects;

protected:
	// �������� ������
	// ������, ��������� �� ������� �������, ����� ����� � �����������, ���������� ������� �� ������ ���� ����������
	void Add(GraphObject2D* const object);

public:
	virtual void Draw(const SDLApplication* app, const Vector& base) const;

};

#endif
