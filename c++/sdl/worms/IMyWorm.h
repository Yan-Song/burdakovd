#ifndef IMYWORM_H
#define IMYWORM_H

#include "IWorm.h"
#include "WormLogic.h"
#include "SDL.h"
#include "CellType.h"

// методы, которые будут использованы только логикой червя
class IMyWorm : public IWorm
{
public:

	// основная логика червя
	virtual WormLogic Run() = 0;

	// нажата ли какая-то клавиша
	virtual bool isPressed(const SDLKey key) const = 0;
	
	// посмотреть какую-то ячейку, занимает у червя некоторое время, чем дальше от него, тем больше
	virtual CellType Look(const int x, const int y) = 0;

	virtual ~IMyWorm()
	{
	}
};

#endif
