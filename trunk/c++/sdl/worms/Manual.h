#ifndef MANUAL_H
#define MANUAL_H

#include "Worm.h"
#include "WormLogic.h"

// лидером у этих червей всегда является старейший (с наименьшим ID)
// если он умирает, то после отстутствия лидера в течение одной секунды, инициируются перевыборы
// в LeaderID хранится текущий ID лидера, если у кого-то ID меньше, то он заменяет его своим, так проходят выборы
// лидер управляется с клавиатуры, остальные следут за ним
class Manual : public Worm
{
private:
	static unsigned int LeaderID;
	static SimplePoint LeaderPosition;
	static double LastLeaderPresenceTime;
public:
	Manual()
	{
		
	}

	virtual WormLogic Run();

	WormLogic FindFood();
	
	void InitiateElections();

	virtual ~Manual()
	{
	}
};

#endif
