#ifndef IENGINE_H
#define IENGINE_H

#include <sdlapplication/Color.h>
#include <sdlapplication/Vector.h>
#include "NormalizedVector3D.h"

namespace RT
{
	class IEngine
	{
	public:
		// ��������� ������������ �������� ����� ����������� � �������� �������� � ���� �����
		// �� ���� �������� ��������� ��, ������� ������� �� �������, ������������ ������� ����� ���������
		// ������������ - dlight/ds
		virtual RealColor CalculateLightness(const Point3D& point, const NormalizedVector3D& n) const = 0;
	};
}

#endif
