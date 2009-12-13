#ifndef WORMSAPPLICATION_H
#define WORMSAPPLICATION_H

#include <vector>

#include <Color.h>
#include <SDLApplication.h>
#include <Timer.h>
#include <Utils.h>

#include "BattleField.h"
#include "CellType.h"
#include "ISimpleGameLoop.h"
#include "ISomeWorm.h"
#include "Registrator.h"


class WormsApplication: public SDLApplication
{
public:
	WormsApplication();

	SharedState CurrentState;

private:
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int ScreenWidth = 800, ScreenHeight = 600;
	Timer printStatsTimer;

protected:
	virtual void ProcessEvent(const SDL_Event& Event);
	virtual void Main();
	virtual void Render();
};

#endif
