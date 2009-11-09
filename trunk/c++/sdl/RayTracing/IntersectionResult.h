#ifndef INTERSECTIONRESULT_H
#define INTERSECTIONRESULT_H

#include "sdlapplication/Vector.h"
#include "NormalizedVector3D.h"
#include "sdlapplication/Utils.h"
#include <stdexcept>

namespace RT
{
	// такие фокусы с Yes/No/Maybe приходится делать потому что
	// RTObject::FindIntersection должна возвращать либо пересечение либо отстутствие пересечения

	
	// пересечение (существующее)
	class Intersection
	{
	private:
		Intersection() {}
		friend class MaybeIntersection;

	public:
		Point3D Point;
		NormalizedVector3D n;
		
		Intersection(const Point3D& _Point, const NormalizedVector3D& _n) : Point(_Point), n(_n)
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
		const Intersection i;

	public:
		const bool Exists;

		MaybeIntersection(const Intersection& intersection) : i(intersection), Exists(true) {}

		MaybeIntersection(const NoIntersection& n) : Exists(false) {}

		inline operator Intersection() const
		{
			if(Exists)
				return Intersection(i);
			else
				throw new std::bad_cast();
		}

		inline operator NoIntersection() const
		{
			if(Exists)
				throw new std::bad_cast();
			else
				return NoIntersection();
		}
	};
}

#endif
