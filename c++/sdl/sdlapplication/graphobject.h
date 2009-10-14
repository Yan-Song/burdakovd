#ifndef GOBJECT_H
#define GOBJECT_H

#include <SDL.h>
#include "matrix.h"
#include "Vector.h"
#include "sdlapplication.h"

// ������, �� ��������� �� ����� ���������
template<int Dimensions>
class GenericGraphObject
{
public:
	typedef GenericVector<double, Dimensions> Vector;

	// ������������ �������
	virtual void Shift(const Vector& v) = 0;

	// ... ������ ��������/����������...
    
    virtual ~GenericGraphObject() {};
};

// ������, ����������� ��� 2D ��������
class GraphObject2D : public GenericGraphObject<2>
{
public:
	// ���������� ���� �� �������� �����������
	virtual void Draw(const SDLApplication*) const = 0;

};

#endif
