#ifndef IRTOBJECT_H
#define IRTOBJECT_H

#include "Ray.h"
#include "Color.h"
#include "NormalizedVector3D.h"
#include "IntersectionResult.h"

namespace RT
{
	class IRTObject
	{
	public:
		// ��������� ����� �� ��� ������������ � ��������
		// ���� ���� ����� ���������� true, �� ��� �� ����������� �����������
		// ���� false - ����������� ����������� �����������
		// ����� ���� �� ������ ����������� ������
		// ������������ ��� ���������������� ���������� �������� � �������� ��� �� ������������
		virtual bool MaybeIntersection(const Ray& ray) const = 0;

		// ���� ����� ���������, ������������ �� ��� � ��������
		// � ���� ��, �� ������� ����� ����������� � ������ ������� � ������� � ���� �����
		// ���� ��� - false
		// �� ����� �������� ����������� ������ ��� MaybeIntersection
		// ������� ��� ����� �������� ������ ���� MaybeIntersection ������ true
		virtual IntersectionResult FindIntersection(const Ray& ray) const = 0;

		// ������� ���� ����� ����������� � �����
		virtual RealColor Trace(const Ray& ray, const IntersectionResult& result) const = 0;

		virtual ~IRTObject() {}
	};

	class RTObject : public IRTObject
	{
	public:
		RealColor color;

		RTObject(const RealColor& _color) : color(_color) {}
	};
}

#endif
