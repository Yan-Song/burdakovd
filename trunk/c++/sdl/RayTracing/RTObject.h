#ifndef IRTOBJECT_H
#define IRTOBJECT_H

#include "Ray.h"
#include "sdlapplication/Color.h"
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
		virtual bool PossibleIntersection(const Ray& ray) const = 0;

		// ���� ����� ���������, ������������ �� ��� � ��������
		// � ���� ��, �� ������� ����� �����������, � ���������� ������ ������� � ��������� ������ ��������� ���� �����
		// �� ����� �������� ����������� ������ ��� PossibleIntersection
		// ������� ��� ����� �������� ������ ���� PossibleIntersection ������ true
		virtual MaybeIntersection FindIntersection(const Ray& ray) const = 0;

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
