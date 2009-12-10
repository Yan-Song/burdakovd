#ifndef ICAMERA_H
#define ICAMERA_H

#include <sdlapplication/Vector.h>
#include "IObject3D.h"
#include "NormalizedVector3D.h"
#include "Ray.h"

namespace RT
{
	class ICamera : public IObject3D
	{
	public:
		virtual void Locate(const Point3D& position) = 0;

		virtual Point3D GetPosition() const = 0;

		virtual void SetDirection(const RT::NormalizedVector3D& direction) = 0;

		virtual RT::NormalizedVector3D GetDirection() const = 0;

		virtual void PickTarget(const Point3D& target) = 0;

		// сгенерировать луч, соответствующий заданной экранной точке
		virtual Ray GenerateRay(const double sx, const double sy) const = 0;

		// переместиться вперёд (или назад, если distance < 0)
		virtual void MoveForward(const double distance) = 0;

		// повернуть камеру по горизонтали (по горизонтали не относительно пространства, а относительно экрана)
		virtual void RotateHorizontal(const double phi) = 0;

		// повернуть камеру по вертикали (по вертикали относительно экрана)
		virtual void RotateVertical(const double phi) = 0;

		virtual ~ICamera() {}
	};
}

#endif
