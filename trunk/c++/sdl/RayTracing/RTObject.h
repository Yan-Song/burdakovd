#ifndef RTOBJECT_H
#define RTOBJECT_H

#include "Ray.h"

namespace RT
{
	class RTObject
	{
	public:
		// проверить пересечение с лучом
		virtual bool CheckIntersection(const Ray& vector) const = 0;

	};
}

#endif
