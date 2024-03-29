#include <sdlapplication/Color.h>
#include <sdlapplication/SDLApplication.h>
#include <sdlapplication/Utils.h>
#include <sdlapplication/Vector.h>
#include "CompoundObject.h"
#include "Frustum.h"
#include "Invisible.h"
#include "Material.h"
#include "Polynom.h"
#include "RTObject.h"
#include "Sphere.h"
#include "Triangle.h"

RT::Frustum::Frustum(const Vector3D &CenterBottom, const double RBottom, const double RTop, const double H, const int count, \
					 const Material &material) : sphere(), has_sphere(false)
{
	assert(count > 1);
	assert(RTop >= 0);
	assert(RBottom >= 0);
	assert(H >= 0);

	const double dphi = 2 * Pi / count;

	const Point3D CenterTop = CenterBottom + Vector3DByCoords(0, 0, H);

	const Point3D FirstBottom = CenterBottom + Vector3DByCoords(RBottom, 0, 0);
	const Point3D FirstTop = CenterTop + Vector3DByCoords(RTop, 0, 0);

	for(int i = 0; i < count; ++i)
	{
		const int next = (i + 1) % count;
		const double phi = dphi * i;
		const double nextphi = dphi * next;

		const Point3D CurrentBottom = CenterBottom + Vector3DByCoords(RBottom * cos(phi), RBottom * sin(phi), 0);
		const Point3D CurrentTop = CenterTop + Vector3DByCoords(RTop * cos(phi), RTop * sin(phi), 0);

		const Point3D NextBottom = CenterBottom + Vector3DByCoords(RBottom * cos(nextphi), RBottom * sin(nextphi), 0);
		const Point3D NextTop = CenterTop + Vector3DByCoords(RTop * cos(nextphi), RTop * sin(nextphi), 0);

		// возможно есть смысл тут группировать грани, чтоб они содержались в одной какой-то сфере
		if(RBottom > 0)
		{
			if(i != 0 && next != 0)
				CompoundObject::Add(RT::CompoundObject::SharedObject(new Triangle(CurrentBottom, NextBottom, FirstBottom, material)));

			CompoundObject::Add(RT::CompoundObject::SharedObject(new Triangle(CurrentBottom, NextBottom, CurrentTop, material)));
		}

		if(RTop > 0)
		{
			if(i != 0 && next != 0)
				CompoundObject::Add(RT::CompoundObject::SharedObject(new Triangle(CurrentTop, NextTop, FirstTop, material)));

			CompoundObject::Add(RT::CompoundObject::SharedObject(new Triangle(CurrentTop, NextTop, NextBottom, material)));
		}
	}
	

	if(H == 0)
	{
		has_sphere = false;
	}
	else
	{
		const double h = (sqr(H) - sqr(RBottom) + sqr(RTop)) / 2 / H;

		const Point3D Center = CenterBottom + Vector3DByCoords(0, 0, h);

		const double R = sqrt(sqr(h) + sqr(RBottom));

		sphere = CompoundObject::SharedObject(new Sphere(Center, R, RT::Material()));

		CompoundObject::Add(CompoundObject::SharedObject(new RT::Invisible(sphere)));

		has_sphere = true;
	}
}

bool RT::Frustum::PossibleIntersection(const RT::Ray &ray) const
{
	if(has_sphere)
	{
		return sphere->PossibleIntersection(ray);
	}
	else
	{
		return CompoundObject::PossibleIntersection(ray);
	}
}

