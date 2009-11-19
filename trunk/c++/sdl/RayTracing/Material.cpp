#include "Material.h"
#include <algorithm>
#include <cmath>
#include "sdlapplication/Utils.h"

RT::Material::Material(const RealColor& _color) : has_texture(false), base(), dx(), dy(), Texture(), color(_color)
{
}

void RT::Material::SetColor(const RealColor &_color)
{
	color = _color;
	has_texture = false;
	Texture.reset();
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
		const ScreenPoint tPoint = static_cast<ScreenPoint>(TexturePoint(MaterialPoint));
	
		return Texture->GetPixel(tPoint[0], tPoint[1]);
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

RealColor RT::Material::Trace(const Point3D &point, const Point2D &MaterialPoint, const RT::NormalizedVector3D &n, const RT::Ray &ray) const
{
	const RealColor PointColor = GetPixel(MaterialPoint);

	return PointColor * std::abs(static_cast<Vector3D>(n) * static_cast<Vector3D>(ray.Vector)) / point.QDistance(ray.Start);
}
