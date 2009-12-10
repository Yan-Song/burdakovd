#include <cmath>
#include "Camera.h"
#include "NormalizedVector3D.h"

class RT::Camera::Util
{
public:
	inline static Point3D DefaultPosition(const double ScreenWidth, const double ScreenHeight)
	{
		return Vector3DByCoords(ScreenWidth / 2, ScreenHeight / 2, -1000.0);
	}

	inline static Point3D ScreenCenter(const Point3D& position, const RT::NormalizedVector3D& direction)
	{
		return position + static_cast<Vector3D>(direction);
	}

	inline static Vector3D ds_(const RT::NormalizedVector3D& ds__dest, const double phi, const double size)
	{
		return static_cast<Vector3D>(ds__dest) * (2.0 * tan(phi * 0.5) / size);
	}
};

RT::Camera::Camera(const double ScreenWidth, const double ScreenHeight, const double HorizontalPhi, const double VerticalPhi) :
			ScreenWidth_(ScreenWidth),
			ScreenHeight_(ScreenHeight),
			HorizontalPhi_(HorizontalPhi),
			VerticalPhi_(VerticalPhi),
			Position(Util::DefaultPosition(ScreenWidth, ScreenHeight)),
			direction(0.0, 0.0, 1.0),
			ScreenCenter(Util::ScreenCenter(Position, direction)),
			dsx(Util::ds_(RT::NormalizedVector3D(1.0, 0.0, 0.0), HorizontalPhi, ScreenWidth)),
			dsy(Util::ds_(RT::NormalizedVector3D(0.0, 1.0, 0.0), VerticalPhi, ScreenHeight))
{
}

void RT::Camera::SetDirection(const RT::NormalizedVector3D& _direction)
{
	direction = _direction;

	const double epsilon = 1e-9;
	const Vector3D dy = Vector3DByCoords(0, 1, 0);
	const Vector3D dz = Vector3DByCoords(0, 0, 1);
	const Vector3D v = static_cast<Vector3D>(direction);

	// сначала находим направление, для этого проецируем dy на экранную плоскость
	const Vector3D dsy_dest__ = dy - v * (dy * v);

	// если получился ноль, то есть плоскость перпендикулярна dy, то берём в качестве dsy_dest проекцию dz на плоскость
	// не очень хорошо, но на самом деле вероятность этого мала
	const Vector3D dsy_dest_ = dsy_dest__.QLength() > epsilon ?
		dsy_dest__
		: dz - v * (dz * v);

	const NormalizedVector3D dsy_dest = static_cast<RT::NormalizedVector3D>(dsy_dest_);

	dsy = Util::ds_(dsy_dest, VerticalPhi_, ScreenHeight_);

	// dsx направлен так чтобы быть перпендикулярным dsy и v, а также быть повернутым вправо
	const Vector3D dsx_dest_ = dsy_dest_ ^ v;

	const NormalizedVector3D dsx_dest = static_cast<RT::NormalizedVector3D>(dsx_dest_);

	dsx = Util::ds_(dsx_dest, HorizontalPhi_, ScreenWidth_);

	ScreenCenter = Util::ScreenCenter(Position, direction);
}

RT::Ray RT::Camera::GenerateRay(const double sx, const double sy) const
{
	// находим 3D точку, соответствующую (sx, sy)
	const Point3D point = ScreenCenter + \
		dsx * (sx - ScreenWidth_ * 0.5) + \
		dsy * (sy - ScreenHeight_ * 0.5);

	return RT::Ray(point - Position, Position);
}

void RT::Camera::Locate(const Point3D& position)
{
	Position = position;
	ScreenCenter = Util::ScreenCenter(Position, direction);
}

Point3D RT::Camera::GetPosition() const
{
	return Position;
}

RT::NormalizedVector3D RT::Camera::GetDirection() const
{
	return direction;
}

void RT::Camera::PickTarget(const Point3D& target)
{
	SetDirection(static_cast<NormalizedVector3D>(target - Position));
}

void RT::Camera::Move(const Vector3D& offset)
{
	Position += offset;
	ScreenCenter += offset;
}

void RT::Camera::Rotate(const Affine::Axe axe, const Point3D& base, const double phi)
{
	GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi, base);

	Position = rotator * Position;
	ScreenCenter = rotator * ScreenCenter;

	GenericMatrix<4> r_rotator = Affine::Rotate3D(axe, phi);

	dsx = r_rotator * dsx;
	dsy = r_rotator * dsy;
	direction = static_cast<NormalizedVector3D>(r_rotator * static_cast<Vector3D>(direction));
}

void RT::Camera::MoveForward(const double distance)
{
	Move(distance * static_cast<Vector3D>(direction));
}

void RT::Camera::RotateHorizontal(const double phi)
{
	// вращаем вокруг оси dsy

	const Vector3D x = dsx * cos(phi) + static_cast<Vector3D>(direction) * sin(phi) * dsx.Length();
	const Vector3D z = static_cast<Vector3D>(direction) * cos(phi) - dsx * sin(phi) / dsx.Length();

	dsx = x;
	direction = static_cast<NormalizedVector3D>(z);

	ScreenCenter = Util::ScreenCenter(Position, direction);
}

void RT::Camera::RotateVertical(const double phi)
{
	// вращаем вокруг оси dsx

	const Vector3D y = dsy * cos(phi) - static_cast<Vector3D>(direction) * sin(phi) * dsy.Length();
	const Vector3D z = static_cast<Vector3D>(direction) * cos(phi) + dsy * sin(phi) / dsy.Length();

	dsy = y;
	direction = static_cast<NormalizedVector3D>(z);

	ScreenCenter = Util::ScreenCenter(Position, direction);
}
