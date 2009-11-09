#ifndef INTERSECTIONRESULT_H
#define INTERSECTIONRESULT_H

#include "sdlapplication/Vector.h"
#include "NormalizedVector3D.h"
#include "sdlapplication/Utils.h"
#include <stdexcept>

namespace RT
{
	// ����� ������ � Yes/No/Maybe ���������� ������ ������ ���
	// RTObject::FindIntersection ������ ���������� ���� ����������� ���� ����������� �����������

	
	// ����������� (������������)
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


	// ���������� �����������
	class NoIntersection
	{
	public:
		NoIntersection() {}
	};

	
	// ��������� �����������
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
