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
	// ����� ������ � Yes/No/Maybe ���������� ������ ������ ���
	// RTObject::FindIntersection ������ ���������� ���� ����������� ���� ���������� �����������

	// � ������ � ITracer - ������ ��� �������� ��� ����������� ����� ����, ������ ����� �������������� ������
	// ������� ����� ���� ��� ��������� � FindIntersection()
	// � ������� ��� ����� - ������ �������

	// ��� CompoundObject ����� ��������� ���� ����� ����� � ����� �� ��������� �������� ���� �����������

	// ��������� ������ ������� ����� �������� ����� ���� ������ ��� ������ �������� - 
	// ������ ��������� ��� ���: ITracer
	// � ������� Trace ���������� ����

	// ����������� (������������)
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
		Intersection i;

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
