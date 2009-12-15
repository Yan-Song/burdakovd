#include "Engine.h"

void Engine::SetState(const SharedState &state)
{
	CurrentState = state;
}

void Engine::SetNextState(const SharedState &state)
{
	NextState = state;
}

void Engine::ChangeState()
{
	if(NextState)
	{
		SetState(NextState);
		NextState = SharedState();
	}
}

SharedState Engine::GetCurrentState() const
{
	return CurrentState;
}
