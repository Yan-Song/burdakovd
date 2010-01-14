#ifndef BATTLE_H
#define BATTLE_H

#include <map>
#include <Timer.h>
#include <UI/ElementSet.h>
#include "BattleField.h"
#include "BattleSettings.h"
#include "ISomeWorm.h"
#include "IWorm.h"

class Engine;

class Battle : public UI::ElementSet
{
private:
	Engine* const app;
	Teams teams;
	typedef std::vector<SharedSomeWorm> WormCollection;
	WormCollection CurrentGeneration, NextGeneration;
	size_t lastWormID;
	::Timer timer;
	typedef std::map<Color, SharedRenderer> Renderers;
	Renderers renderers;
	
	class Util;

private:
	Battle(const Battle& );
	Battle& operator =(const Battle& );

	// выбрать пустую ячейку случайным образом
	SimplePoint GetFreeCell() const;


public:
	BattleField Field;

public:
	Battle(Engine* const app_, const Teams& teams_);

	virtual void Render();

	double GetTime() const;
};

#endif
