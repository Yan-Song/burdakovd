#ifndef BATTLE_H
#define BATTLE_H

#include <UI/ElementSet.h>
#include "BattleField.h"
#include "BattleSettings.h"

class Engine;

class Battle : public UI::ElementSet
{
private:
	Engine* const app;
	Teams teams;
	
	class Util;

private:
	Battle(const Battle& );
	Battle& operator =(const Battle& );

public:
	BattleField Field;

public:
	Battle(Engine* const app_, const Teams& teams_);

	virtual void Render();
};

#endif
