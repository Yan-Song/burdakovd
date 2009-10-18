#ifndef STATUE_H
#define STATUE_H

#include "Worm.h"
#include "WormLogic.h"

class Statue : public Worm
{
public:
	Statue()
	{

	}

	virtual WormLogic Run()
	{
		return Stay;
	}

	~Statue()
	{
	}
};

#endif
