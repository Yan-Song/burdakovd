#ifndef SURFACE_H
#define SURFACE_H

#include "CompoundObject.h"
#include "Color.h"
#include "Segment.h"

// класс, строящий поверхность, заданную функцией z = z(x, y)
// в виде сетки с заданным шагом
class Surface : public CompoundObject3D
{
public:
	template<class Func>
	Surface(const Func& f,
		const double Xmin, const double Ymin,
		const double Xmax, const double Ymax,
		const double dx, const double dy,
		const Color& color)
	{
		for(double x = Xmin; x < Xmax; x += dx)
			for(double y = Ymin; y < Ymax; y += dy)
			{
				double z = f(x, y);
				Point3D p = Vector3DByCoords(x, y, z);

				if(x + dx < Xmax)
				{
					Add(new Segment3D(p, Vector3DByCoords(x + dx, y, f(x + dx, y)), color));
				}

				if(y + dy < Ymax)
				{
					Add(new Segment3D(p, Vector3DByCoords(x, y + dy, f(x, y + dy)), color));
				}
			}
	}
};

#endif