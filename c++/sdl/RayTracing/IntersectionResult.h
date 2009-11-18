#ifndef INTERSECTIONRESULT_H
#define INTERSECTIONRESULT_H

#include "sdlapplication/Vector.h"
#include "NormalizedVector3D.h"
#include "sdlapplication/Utils.h"
#include <stdexcept>
#include <memory>
#include "ITracer.h"

namespace RT
{
	// такие фокусы с Yes/No/Maybe приходится делать потому что
	// RTObject::FindIntersection должна возвращать либо пересечение либо отсутствие пересечения

	// А фокусы с ITracer - потому что объектам для определения цвета луча, бывают нужны дополнительные данные
	// которые могли быть уже вычислены в FindIntersection()
	// К примеру для сферы - вектор нормали

	// Для CompoundObject чтобы вычислить цвет нужно знать с каким из вложенных объектов было пересечение

	// поскольку данные которые нужно передать могут быть разные для разных объектов - 
	// сделал интерфейс для них: ITracer
	// и функцию Trace переместил туда

	// пересечение (существующее)
	class Intersection
	{
	private:
		Intersection() {}
		friend class MaybeIntersection;

	public:
		Point3D Point;
		SharedTracer Tracer;
		
		Intersection(const Point3D& _Point, const SharedTracer& _Tracer)
			: Point(_Point), Tracer(_Tracer)
		{
		}
	};


	// отсутствие пересечения
	class NoIntersection
	{
	public:
		NoIntersection() {}
	};

	
	// возможное пересечение
	class MaybeIntersection
	{
	private:
		Intersection i;

	public:
		bool Exists;

		MaybeIntersection(const Intersection& intersection) : i(intersection), Exists(true) {}

		MaybeIntersection(const NoIntersection& ) : Exists(false) {}

		inline operator Intersection() const
		{
			if(Exists)
				return Intersection(i);
			else
				throw std::bad_cast();
		}

		inline operator NoIntersection() const
		{
			if(Exists)
				throw std::bad_cast();
			else
				return NoIntersection();
		}
	};
}

#endif
