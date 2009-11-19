#ifndef ITRACER_H
#define ITRACER_H

#include <sdlapplication/Color.h>
#include <sdlapplication/Shared.h>
#include "IEngine.h"
#include "Ray.h"

namespace RT
{
	class ITracer
	{
	public:
		// вернуть цвет точки пересечения с лучом
		virtual RealColor Trace(const IEngine* engine) = 0;

		virtual ~ITracer() {}
	};

	typedef Shared::shared_ptr<ITracer> SharedTracer;
}

#endif
