#ifndef BATTLE_H
#define BATTLE_H

#include <map>
#include <Timer.h>
#include <UI/ElementSet.h>
#include <Sprite.h>
#include "BattleField.h"
#include "BattleSettings.h"
#include "ISomeWorm.h"
#include "IWorm.h"
#include "Registrator.h"

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
	int foodMade;
	
	class Util;
	friend class Util;

private:
	Battle(const Battle& );
	Battle& operator =(const Battle& );

	const SharedSprite background;

	// выбрать пустую ячейку случайным образом
	SimplePoint GetFreeCell() const;

	SharedRenderer GetRenderer(const Color& color);

public:
	BattleField Field;
	Registrator registrator;

public:
	Battle(Engine* const app_, const Teams& teams_);

	SharedSomeWorm AddWorm(const size_t classID, const double initialEnergy, const TPosition& initialPosition, const SharedRenderer& renderer);

	void MakeFood(const int x, const int y, const int r);

	virtual void Main();

	virtual void Render();

	double GetTime() const;
};

#endif
