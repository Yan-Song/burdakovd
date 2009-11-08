#include "Pencil.h"
#include "Prism.h"
#include "Pyramid.h"
#include "Frustum.h"

Pencil::Pencil(const Vector3D& center, const double length, const Color &outside, const Color &wood, const Color &inside)
{
	Center = center;

	// делаем всё в абсолютных координатах, потом отмасштабируем и сместим как надо
	const double R1 = 1.5;
	const double R2 = 7.5;

	const double H1 = 4.5;
	const double H2 = 18;
	const double H3 = 150;
	const double H4 = 0.1;
	const double H5 = 0.1;
	const double H = H1 + H2 + H3 + H4 + H5;

	const Vector3D corrector = Vector3DByCoords(0, 0, H / 2);

	const Vector3D Center1 = Vector3DByCoords(0, 0, H1 / 2) - corrector;
	const Vector3D Center2 = Vector3DByCoords(0, 0, H1 + H2 / 2) - corrector;
	const Vector3D Center3 = Vector3DByCoords(0, 0, H1 + H2 + H3 / 2) - corrector;
	const Vector3D Center4 = Vector3DByCoords(0, 0, H1 + H2 + H3 + H4 / 2) - corrector;
	const Vector3D Center5 = Vector3DByCoords(0, 0, H1 + H2 + H3 + H4 + H5 / 2) - corrector;

	// грифель
	Pyramid* gr = new Pyramid(Center1, R1, H1, 50, inside);
	gr->Scale(Vector3DByCoords(1, 1, -1));
	CompoundObject3D::Add(gr);

	// деревянная часть
	CompoundObject3D::Add(new Frustum(Center2, R1, R2, H2, 50, wood));

	// основная часть
	CompoundObject3D::Add(new Prism(Center3, R2, H3, 50, outside));

	// наклейка "под дерево"
	CompoundObject3D::Add(new Prism(Center4, R2, H4, 50, wood));

	// наклейка "под грифель"
	CompoundObject3D::Add(new Prism(Center5, R1, H5, 50, inside));

	// и масштаб
	Scale(Vector111 * length / H);
}
