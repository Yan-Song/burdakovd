#ifndef DEMO_H
#define DEMO_H

#include "sdlapplication/SDLApplication.h"
#include "Scene.h"
#include "CompoundObject.h"
#include "Shared.h"

class RTDemoApplication : public SDLApplication
{
private:
	bool Dirty;
	bool Rendered;
	const RT::shared_ptr<RT::Scene> scene;
	const RT::shared_ptr<RT::CompoundObject> container;
	int Quality;

protected:
	static const int ScreenWidth = 800, ScreenHeight = 600;

	virtual void Main();

	virtual void ProcessEvent(SDL_Event);

	virtual void InitialRender();

	void Navigate();

public:
	RTDemoApplication();

	bool Callback(const double percent, const bool AllowBreak);

	virtual ~RTDemoApplication();
	
};

#endif
