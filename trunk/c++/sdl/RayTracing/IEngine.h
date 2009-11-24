#ifndef IENGINE_H
#define IENGINE_H

#include <sdlapplication/Color.h>
#include <sdlapplication/Vector.h>

namespace RT
{
	class NormalizedVector3D;
	class Ray;

	class IEngine
	{
	public:
		// посчитать освещенность заданной точки поверхности с заданной нормалью в этой точке
		// из двух нормалей передаётся та, которая исходит со стороны, освещенность которой нужно посчитать
		// освещенность - dlight/ds
		virtual RealColor CalculateLightness(const Point3D& point, const NormalizedVector3D& n) const = 0;

		virtual RealColor Trace(const RT::Ray& ray) const = 0;

		virtual ~IEngine() {}
	};
}

#endif
