#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "CompoundObject.h"
#include "Vector.h"
#include "Color.h"

// ����� ��������� ��������, � ����, ������������ OZ
// precision � ������������ - ��� ���������� ������ � ����������
class Frustum : public CompoundObject3D
{
public:
	Frustum(const Vector3D& center, const double RBottom, const double RTop, const double H, const int precision, const Color& color);
};

#endif
