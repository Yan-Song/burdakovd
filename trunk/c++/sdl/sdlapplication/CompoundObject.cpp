#include "CompoundObject.h"
#include "Affine.h"

void CompoundObject2D::Add(GraphObject2D* const object)
{
	objects.push_back(object);
}

void CompoundObject2D::Draw(SDLApplication* const app, const Vector& base) const
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Draw(app, base + Center);
}

void CompoundObject2D::Rotate(const double phi)
{
	// повращать все вложенные объекты, относительно нашего центра (в их координатах это начало координат)
	for(ObjectList::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->RotateAround(phi, Vector00);
}

void CompoundObject2D::Scale(const Vector2D& coefficients)
{
	// растянуть все вложенные объекты относительно нашего центра (в их координатах это 0)
	for(ObjectList::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->ScaleRelative(coefficients, Vector00);
}

void CompoundObject3D::Add(GraphObject3D *const object)
{
	objects.push_back(object);
}

void CompoundObject3D::Draw(const Vector3D& base, ITriangleDrawer* const drawer) const
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Draw(base + Center, drawer);
}

void CompoundObject3D::Rotate(const int axe, const double phi)
{
	const GenericMatrix<4> rotator = Affine::Rotate3D(axe, phi);

	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->RotateRelative(axe, phi, Vector000);
}


void CompoundObject3D::Scale(const Vector3D &coefficients)
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->ScaleRelative(coefficients, Vector000);
}

CompoundObject2D::~CompoundObject2D()
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		delete (*it);
}

CompoundObject3D::~CompoundObject3D()
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		delete (*it);
}
