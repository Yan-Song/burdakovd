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
		// ������� ���� ����� ����������� � �����
		virtual RealColor Trace() = 0;

		virtual ~ITracer() {}
	};

	typedef shared_ptr<ITracer> SharedTracer;
};

#endif
