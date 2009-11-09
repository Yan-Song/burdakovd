#include "CompoundObject.h"
#include "IntersectionResult.h"
#include <algorithm>
#include <list>

void RT::CompoundObject::Add(RT::IRTObject *object)
{
	objects.push_back(object);
}

RT::MaybeIntersection RT::CompoundObject::FindIntersection(const RT::Ray &ray) const
{
	// составляем список пересечений дочерних объектов с лучом
	std::list<RT::Intersection> intersections;
	
	for(ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
		if((*it)->PossibleIntersection(ray))
		{
			RT::MaybeIntersection result = (*it)->FindIntersection(ray);
			
			if(result.Exists)
				intersections.push_back(result);
		}

	// если список пуст, то пересечения нет, иначе выбираем ближайшее
	if(intersections.empty())
		return RT::NoIntersection();
	else
	{
		RT::Intersection ans = *intersections.begin();

		for(std::list<RT::Intersection>::const_iterator it = intersections.begin(); it != intersections.end(); ++it)
			if(ray.Start.Distance(it->Point) < ray.Start.Distance(ans.Point))
				ans = *it;

		return ans;
	}
}
