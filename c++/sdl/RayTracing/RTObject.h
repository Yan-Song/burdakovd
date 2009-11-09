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
		// проверить может ли луч пересекаться с объектом
		// если этот метод возвращает true, то это не гарантирует пересечения
		// если false - гарантирует отстутствие пересечения
		// кроме того он должен выполняться быстро
		// используется для предварительного исключения объектов с которыми луч не пересекается
		virtual bool PossibleIntersection(const Ray& ray) const = 0;

		// этот метод проверяет, пересекается ли луч с объектом
		// и если да, то находит точку пересечения, и возвращает объект который в дальнеёшем сможет посчитать цвет точки
		// он может работать значительно дольше чем PossibleIntersection
		// поэтому его стоит вызывать только если PossibleIntersection вернул true
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
