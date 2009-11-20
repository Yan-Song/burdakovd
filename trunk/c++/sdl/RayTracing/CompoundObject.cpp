#include <algorithm>
#include <sdlapplication/Vector.h>
#include "CompoundObject.h"
#include "IntersectionResult.h"

void RT::CompoundObject::Add(const RT::CompoundObject::SharedObject& object)
{
	objects.push_back(object);
}

RT::MaybeIntersection RT::CompoundObject::FindIntersection(const RT::Ray &ray) const
{
	bool found = false;
	double minqdistance = 1e30;
	Intersection ans(Vector000, RT::SharedTracer());

	// обходим все объекты, и находим ближайшее пересечение
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		if((*it)->PossibleIntersection(ray))
		{
			RT::MaybeIntersection result = (*it)->FindIntersection(ray);

			if(result.Exists)
			{
				RT::Intersection intersection(result);

				const double qdistance = ray.Start.QDistance(intersection.Point);

				if(qdistance < minqdistance)
				{
					minqdistance = qdistance;
					ans = intersection;
					found = true;
				}
			}
		}

	if(found)
	{
		return ans;
	}
	else
	{
		return NoIntersection();
	}
}

bool RT::CompoundObject::PossibleIntersection(const RT::Ray& ) const
{
	return true;
}

void RT::CompoundObject::Rotate(const Affine::Axe axe, const Point3D &base, const double phi)
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Rotate(axe, base, phi);
}

void RT::CompoundObject::Move(const Vector3D &offset)
{
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Move(offset);
}
