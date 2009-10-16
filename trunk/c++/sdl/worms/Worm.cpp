#include "Worm.h"
#include "WormsApplication.h"

void Worm::FullRender() const
{
	for(unsigned int i = 0; i < position.size(); ++i)
		app->DrawWormCell(position[i], this);
}
