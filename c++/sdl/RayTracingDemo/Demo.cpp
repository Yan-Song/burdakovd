#include "Demo.h"
#include "SDL.h"
#include "Sphere.h"
#include "Ray.h"
#include "IntersectionResult.h"
#include <iostream>
#include <sstream>
#include <Scene.h>

// x - вправо
// y - вверх
// z - вперед

RTDemoApplication::RTDemoApplication()
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SDL_WM_SetCaption("Ray Tracing Demo", NULL);
}

class Callback : public RT::Scene::ICallback
{
private:
	RTDemoApplication* const app;

public:
	Callback(RTDemoApplication* const _app) : app(_app) {}

	virtual bool call(const double percent)
	{
		return app->Callback(percent);
	}
};

bool RTDemoApplication::Callback(const double percent)
{
	// вывести прогресс
	std::ostringstream os;
	os<<"Ray Tracing Demo. Rendered: "<<static_cast<int>(percent)<<"%";
	SetCaption(os.str());
	
	// обработать ввод пользователя
	ProcessEvents();

	// прервать процесс если приложение пора закрывать
	return !(Running);
}

void RTDemoApplication::InitialRender()
{
	const double startTime = GetTime();

	// Наблюдатель находится перед экраном на расстоянии 1000 пикселов
	const Point3D SpectatorPosition = Vector3DByCoords(ScreenWidth / 2, ScreenHeight / 2, -1000);

	// создаём сцену
	RT::Scene scene(SpectatorPosition);

	// наполняем её шарами
	scene.Add(RT::CompoundObject::SharedObject(new RT::Sphere(Vector3DByCoords(320, 240, 100), 50, Palette::Blue)));
	scene.Add(RT::CompoundObject::SharedObject(new RT::Sphere(Vector3DByCoords(300, 200, 000), 20, Palette::Green)));
	scene.Add(RT::CompoundObject::SharedObject(new RT::Sphere(Vector3DByCoords(700, 300, 100), 100, Palette::Red)));

	// рисуем
	scene.Render(this, RT::Scene::SharedCallback(new ::Callback(this)));

	const int elapsed = static_cast<int>((GetTime() - startTime) * 1000);

	std::cout<<"Initial render "<<(Running ? "completed" : "interrupted")<<" after "<<elapsed<<" ms."<<std::endl;
}

void RTDemoApplication::Main()
{

}

void RTDemoApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();
	}
}

RTDemoApplication::~RTDemoApplication()
{

}

