#ifndef MANUAL_H
#define MANUAL_H

#include "Worm.h"
#include "WormLogic.h"

class Manual : public Worm
{
public:
	Manual()
	{

	}

	virtual WormLogic Run()
	{
		if(isPressed(SDLK_RIGHT))
			return GoRight;
		else if(isPressed(SDLK_LEFT))
			return GoLeft;
		else if(isPressed(SDLK_UP))
			return GoUp;
		else if(isPressed(SDLK_DOWN))
			return GoDown;
		return Stay;
	}

	virtual ~Manual()
	{
	}
};

#endif
