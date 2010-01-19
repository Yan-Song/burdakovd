#ifndef RANDOMEATER_H
#define RANDOMEATER_H

#include "Worm.h"
#include "WormLogic.h"

class RandomEater : public Worm
{
public:
	RandomEater()
	{

	}

	virtual WormLogic Run()
	{
		const SimplePoint head = Position().front();

		if(Look(head.X + 1, head.Y) == CellFood)
			return GoRight;
		if(Look(head.X - 1, head.Y) == CellFood)
			return GoLeft;
		if(Look(head.X, head.Y + 1) == CellFood)
			return GoUp;
		if(Look(head.X, head.Y - 1) == CellFood)
			return GoDown;

		return static_cast<WormLogic>(Rand(1, 4));
	}

	virtual ~RandomEater()
	{
	}
};

#endif
