#ifndef DEMO_H
#define DEMO_H

#include <sdlapplication/SDLApplication.h>
#include <sdlapplication/Shared.h>
#include <sdlapplication/Vector.h>
#include <CompoundObject.h>
#include <ICamera.h>
#include <Scene.h>

class RTDemoApplication : public SDLApplication
{
private:
	const Shared::shared_ptr<RT::Scene> scene;
	const Shared::shared_ptr<RT::CompoundObject> container;
	const RT::Scene::SharedCamera camera;
	const Point3D Center;
	bool Rendered, Dirty;

protected:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const double MovementSpeed;
	static const double RotationSpeed;
	static const double MouseSensitivity;

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
