#ifndef ENGINE_H
#define ENGINE_H

#include <ISimpleGameLoop.h>
#include <SDLApplication.h>

class Engine : public SDLApplication
{
private:
	SharedState CurrentState, NextState;

public:
	Engine() : SDLApplication(), CurrentState(), NextState()
	{
	}

	SharedState GetCurrentState() const;
	
	void SetNextState(const SharedState& state);

protected:
	void ChangeState();

	void SetState(const SharedState& state);
};

#endif
