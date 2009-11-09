#ifndef ITRACER_H
#define ITRACER_H

#include "sdlapplication/Color.h"
#include "Ray.h"
#include "Shared.h"

namespace RT
{
	class ITracer
	{
	public:
		// вернуть цвет точки пересечения с лучом
		virtual RealColor Trace() = 0;

		virtual ~ITracer() {}
	};

	typedef shared_ptr<ITracer> SharedTracer;
};

#endif
