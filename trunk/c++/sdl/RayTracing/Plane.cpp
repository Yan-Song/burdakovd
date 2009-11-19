#include "Plane.h"

namespace
{
	class Tracer : public RT::ITracer
	{
	private:
		const Point3D base, point;
		const Vector3D du, dv;
		const RT::Material material;
		const RT::Ray ray;

		Tracer(const Tracer& );
		Tracer operator=(const Tracer& );

	public:
		Tracer(const Point3D& _base, const Point3D& _point, const Vector3D& _du, const Vector3D& _dv, const RT::Material& _material, \
			const RT::Ray& _ray) :
		  base(_base), point(_point), du(_du), dv(_dv), material(_material), ray(_ray)
		{
		}
		
		virtual RealColor Trace(const RT::IEngine* engine)
		{
			const Vector3D p = point - base;

			const Vector3D vn = du ^ dv;
			const RT::NormalizedVector3D n(vn);
			
			const double vnql = vn.QLength();
			
			const double u = (p ^ dv) * vn / vnql;
			const double v = (p ^ du) * vn / vnql;

			return material.Trace(point, Vector2DByCoords(u, v), n, ray, engine);
		}
	};
}

RT::MaybeIntersection RT::Plane::FindIntersection(const RT::Ray &ray) const
{
	const Vector3D n = du ^ dv;
	const Vector3D v(ray.Vector);

	const double z = n * v;

	if(z == 0)
	{
		return RT::NoIntersection();
	}
	else
	{
		const double t = (n * (Center - ray.Start)) / z;

		if(t > 0)
		{

			const Point3D point = ray.Start + t * v;

			RT::SharedTracer tracer(new Tracer(Center, point, du, dv, material, ray));

			return Intersection(point, tracer);
		}
		else
		{
			return RT::NoIntersection();
		}
	}
}
