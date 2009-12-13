#ifndef IGAMELOOP_H
#define IGAMELOOP_H

#include "ISimpleGameLoop.h"

class IGameLoop : public ISimpleGameLoop
{
public:
	virtual void ProcessEvents() = 0;
};

#endif
