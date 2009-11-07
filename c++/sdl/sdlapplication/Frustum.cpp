#include "Frustum.h"
#include "Color.h"
#include "Vector.h"
#include "Triangle3D.h"
#include "Tetragon.h"
#include "CompoundObject.h"
#include <cmath>
#include "Utils.h"

Frustum::Frustum(const Vector3D &center, const double RBottom, const double RTop, const double H, const int precision, const Color &color)
{
	Center = center;

	double dphi = 2 * Pi / precision;

	const Vector3D TopCenter = Vector3DByCoords(0, 0, H / 2);
	const Vector3D BottomCenter = -TopCenter;

	for(int i = 0; i < precision; ++i)
	{
		const double phi = dphi * i;
		const double nextphi = phi + dphi;

		const Vector3D TopCurrent = TopCenter + RTop * Vector3DByCoords(cos(phi), sin(phi), 0);
		const Vector3D TopNext = TopCenter + RTop * Vector3DByCoords(cos(nextphi), sin(nextphi), 0);

		const Vector3D BottomCurrent = BottomCenter + RBottom * Vector3DByCoords(cos(phi), sin(phi), 0);
		const Vector3D BottomNext = BottomCenter + RBottom * Vector3DByCoords(cos(nextphi), sin(nextphi), 0);

		if(RTop > 0)
			CompoundObject3D::Add(new Triangle3D(TopCurrent, TopNext, TopCenter, color));

		if(RBottom > 0)
			CompoundObject3D::Add(new Triangle3D(BottomNext, BottomCurrent, BottomCenter, color));

		if(H > 0)
			CompoundObject3D::Add(new Tetragon(BottomCurrent, BottomNext, TopNext, TopCurrent, color));
	}
}
