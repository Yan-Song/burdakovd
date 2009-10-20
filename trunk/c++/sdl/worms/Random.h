#ifndef RANDOM_H
#define RANDOM_H

#include "Worm.h"
#include "WormLogic.h"

class Random : public Worm
{
public:
	Random()
	{

	}

	virtual WormLogic Run()
	{
		int decision = Rand(0, 3);

		if(decision == 0)
			return GoUp;
		else if (decision == 1)
			return GoDown;
		else if (decision == 2)
			return GoLeft;
		else
			return GoRight;
	}

	virtual ~Random()
	{
	}
};

#endif
