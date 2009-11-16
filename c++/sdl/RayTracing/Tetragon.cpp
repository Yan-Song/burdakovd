#include "Tetragon.h"
#include "NormalizedVector3D.h"

// Это будет работать только если a, b, c, d в одной плоскости
RT::Tetragon::Tetragon(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& d, const Material& material)
{
	// первый треугольник, для него материал менять не надо (ab - dx, ad - dy)
	CompoundObject::Add(CompoundObject::SharedObject(new Triangle(a, b, d, material)));

	// второй треугольник bcd
	// для него bc - dx, bd - dy, b - база
	const RT::NormalizedVector3D dx = b - a;
	const RT::NormalizedVector3D dy = d - a;

	const double z = (static_cast<Vector3D>(dx) ^ static_cast<Vector3D>(dy)).Length();

	const double u = ((c - a) ^ static_cast<Vector3D>(dy)).Length() / z;
	const double v = ((c - a) ^ static_cast<Vector3D>(dx)).Length() / z;
	const Point2D C_ = Vector2DByCoords(u, v);
	const Point2D B_ = Vector2DByCoords((b - a).Length(), 0);
	const Point2D D_ = Vector2DByCoords(0, (d - a).Length());

	const Vector2D newbase = B_;
	const Vector2D newdx = (C_ - B_) / (C_ - B_).Length();
	const Vector2D newdy = (D_ - B_) / (D_ - B_).Length();

	CompoundObject::Add(CompoundObject::SharedObject(new Triangle(b, c, d, material.Cut(newbase, newdx, newdy))));
}
