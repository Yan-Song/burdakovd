#ifndef DEMO_H
#define DEMO_H

#include "sdlapplication/SDLApplication.h"

class RTDemoApplication : public SDLApplication
{
protected:
	static const int ScreenWidth = 800, ScreenHeight = 600;

	virtual void Main();

	virtual void ProcessEvent(SDL_Event);

	virtual void InitialRender();

public:
	RTDemoApplication();

	bool Callback(const double percent);

	virtual ~RTDemoApplication();
	
};

#endif