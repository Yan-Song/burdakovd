#include <algorithm>
#include <cmath>
#include <sdlapplication/Utils.h>
#include "Material.h"
 
RT::Material::Material(const RealColor& _color) : has_texture(false), base(false), \
dx(false), dy(false), Texture(), color(_color), Reflection(0.0)
{
}

void RT::Material::SetColor(const RealColor &_color)
{
	color = _color;
	has_texture = false;
	Texture.reset();
}

void RT::Material::SetReflection(const double reflection)
{
	assert(reflection < 1);
	Reflection = reflection;
}

void RT::Material::SetTexture(const RT::Material::SharedTexture &texture, const Point2D &_base, const Vector2D &_dx, const Vector2D &_dy)
{
	Texture = texture;
	base = _base;
	dx = _dx;
	dy = _dy;
	has_texture = true;
}

RT::Material RT::Material::Cut(const Point2D &base, const Vector2D &dx, const Vector2D &dy) const
{
	RT::Material m(*this);

	m.base = TexturePoint(base);
	m.dx = TexturePoint(dx);
	m.dy = TexturePoint(dy);

	return m;
}

RealColor RT::Material::GetPixel(const Point2D& MaterialPoint) const
{
	if(has_texture)
	{
		const Point2D tPoint = TexturePoint(MaterialPoint);
	
		return Texture->GetPixel(iround(tPoint[0]), iround(tPoint[1]));
	}
	else
	{
		return color;
	}
}

Point2D RT::Material::TexturePoint(const Point2D &MaterialPoint) const
{
	return base + MaterialPoint[0] * dx + MaterialPoint[1] * dy;
}

RealColor RT::Material::Trace(const Point3D &point, const Point2D &MaterialPoint, const RT::NormalizedVector3D &n, \
							  const RT::Ray &ray, const RT::IEngine* engine) const
{
	const RealColor PointColor = GetPixel(MaterialPoint);

	// находим из двух нормалей ту, которая направлена к зрителю
	const NormalizedVector3D zn = static_cast<Vector3D>(n) * static_cast<Vector3D>(ray.Vector) > 0 ?
		NormalizedVector3D(-static_cast<Vector3D>(n)) : n;

	const RealColor AmbientColor = (1.0 - Reflection) * PointColor * engine->CalculateLightness(point, zn);

	if(Reflection > 0)
	{
		const Vector3D v = static_cast<Vector3D>(ray.Vector);
		const Vector3D znv = static_cast<Vector3D>(zn);

		const Vector3D ReflectedVector = v - 2.0 * znv * (znv * v);
		const Vector3D eps = ReflectedVector / ReflectedVector.Length() * 1e-6;

		const RT::Ray ReflectedRay = RT::Ray(ReflectedVector, point + eps, Reflection * ray.Power);

		const RealColor ReflectionColor = Reflection * engine->Trace(ReflectedRay);

		return AmbientColor + ReflectionColor;
	}
	else
	{
		return AmbientColor;
	}
}
