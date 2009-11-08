#ifndef IRTOBJECT_H
#define IRTOBJECT_H

#include "Ray.h"

namespace RT
{
	class IRTObject
	{
	public:
		// ��������� ����������� � �����
		virtual bool CheckIntersection(const Ray& vector) const = 0;

	};
}

#endif
