#ifndef IMYWORM_H
#define IMYWORM_H

#include "IWorm.h"
#include "WormLogic.h"
#include "SDL.h"

// методы, которые будут использованы только логикой червя
class IMyWorm : public IWorm
{
public:

	// основная логика червя
	virtual WormLogic Run() = 0;

	virtual bool isPressed(const SDLKey key) const = 0;

	virtual ~IMyWorm()
	{
	}
};

#endif
