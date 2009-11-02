#include "MyScene.h"

void MyScene::Tick(const double dt)
{
	for(ObjectList::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		(*it)->Move(Vector2DByCoords(- 100 * dt, 0));

		while((*it)->Center[0] < - Width / 2)
			(*it)->Center[0] += Width;
	}
}
