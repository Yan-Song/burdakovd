#ifndef DEMO_H
#define DEMO_H

#include "sdlapplication/SDLApplication.h"
#include "sdlapplication/Vector.h"
#include "Scene.h"
#include "CompoundObject.h"
#include "sdlapplication/Shared.h"

class RTDemoApplication : public SDLApplication
{
private:
	const Shared::shared_ptr<RT::Scene> scene;
	const Shared::shared_ptr<RT::CompoundObject> container;
	Point3D Center;
	bool Rendered, Dirty;

protected:
	static const int ScreenWidth = 800, ScreenHeight = 600;

	virtual void Main();

	virtual void ProcessEvent(SDL_Event);

	virtual void InitialRender();

	void Navigate();

public:
	RTDemoApplication();

	bool Callback(const double percent, const bool AllowBreak, const unsigned int Step, const unsigned int extra);

	virtual ~RTDemoApplication();
	
};

#endif
