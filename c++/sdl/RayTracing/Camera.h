#ifndef CAMERA_H
#define CAMERA_H

#include <sdlapplication/Matrix.h>
#include <sdlapplication/Utils.h>
#include <sdlapplication/Vector.h>
#include "ICamera.h"
#include "NormalizedVector3D.h"
#include "Ray.h"

namespace RT
{
	class Camera : public ICamera
	{
	private:
		class Util;

	private:
		double ScreenWidth_, ScreenHeight_;
		double HorizontalPhi_, VerticalPhi_;
		Point3D Position;
		NormalizedVector3D direction;

		Point3D ScreenCenter;
		Vector3D dsx, dsy;

	public:
		Camera(const double ScreenWidth, const double ScreenHeight, const double HorizontalPhi, const double VerticalPhi);
		
		virtual void Locate(const Point3D& position);

		virtual Point3D GetPosition() const;

		virtual void SetDirection(const RT::NormalizedVector3D& direction);

		virtual RT::NormalizedVector3D GetDirection() const;

		virtual void PickTarget(const Point3D& target);
		
		virtual void Move(const Vector3D& offset);

		virtual void Rotate(const Affine::Axe axe, const Point3D& base, const double phi);

		RT::Ray GenerateRay(const double sx, const double sy) const;
	};
}

#endif
