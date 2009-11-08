#ifndef IRTOBJECT_H
#define IRTOBJECT_H

#include "Ray.h"

namespace RT
{
	class IRTObject
	{
	public:
		// ��������� ����������� � �����
		virtual bool CheckIntersection(const Ray& ray) const = 0;

		virtual ~IRTObject() {}
	};
}

#endif
