#include "Demo.h"
#include "SDL.h"
#include "Sphere.h"
#include "Ray.h"
#include "IntersectionResult.h"
#include <iostream>
#include <sstream>
#include <Scene.h>
#include <CompoundObject.h>
#include "sdlapplication/Affine.h"

// x - вправо
// y - вверх
// z - вперед

RTDemoApplication::RTDemoApplication() : 
	// Наблюдатель находится перед экраном на расстоянии 1000 пикселов
	scene(RT::shared_ptr<RT::Scene>(new RT::Scene(Vector3DByCoords(ScreenWidth / 2, ScreenHeight / 2, -1000)))),
		container(new RT::CompoundObject()),
		Rendered(false), Dirty(false)
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SDL_WM_SetCaption("Ray Tracing Demo", NULL);

	// наполняем контейнер шарами
	container->Add(RT::CompoundObject::SharedObject(new RT::Sphere(Vector3DByCoords(320, 240, 600), 50, Palette::Blue)));
	container->Add(RT::CompoundObject::SharedObject(new RT::Sphere(Vector3DByCoords(300, 200, 500), 20, Palette::Green)));
	container->Add(RT::CompoundObject::SharedObject(new RT::Sphere(Vector3DByCoords(400, 200, 000), 20, Palette::Green)));
	container->Add(RT::CompoundObject::SharedObject(new RT::Sphere(Vector3DByCoords(700, 300, 600), 100, Palette::Red)));

	// добавляем его в сцену
	scene->Add(container);
}

template<bool AllowBreak>
class Callback : public RT::Scene::ICallback
{
private:
	RTDemoApplication* const app;

public:
	Callback(RTDemoApplication* const _app) : app(_app) {}

	virtual bool call(const double percent)
	{
		if(AllowBreak)
			return app->Callback(percent);
		else
		{
			app->Callback(percent);
			return false;
		}
	}
};

bool RTDemoApplication::Callback(const double percent)
{
	// вывести прогресс
	std::ostringstream os;
	os<<"Ray Tracing Demo. Rendered: "<<static_cast<int>(percent)<<"%. ";
	os<<"Quality: "<<Quality;
	SetCaption(os.str());
	
	UpdateStats();
	// обработать ввод пользователя
	ProcessEvents();
	Navigate();

	// прервать процесс если приложение пора закрывать или картинка уже устарела
	return (!(Running)) || Dirty;
}

void RTDemoApplication::InitialRender()
{
	ClearScreen();
}

void RTDemoApplication::Navigate()
{
	if(isPressed(SDLK_RIGHT))
	{
		Dirty = true;
		container->Rotate(Affine::Y, Vector3DByCoords(ScreenWidth / 2, 0, 500), dt);
	}

	if(isPressed(SDLK_LEFT))
	{
		Dirty = true;
		container->Rotate(Affine::Y, Vector3DByCoords(ScreenWidth / 2, 0, 500), -dt);
	}
}

void RTDemoApplication::Main()
{
	Navigate();
	
	if(Dirty)
		Rendered = false;

	// после того картинка отрисована, заново это делать не надо
	if(Rendered)
	{
		return;
	}

	Dirty = false;

	const double startTime = GetTime();

	const int startQuality = 8;

	// рисовать, постепенно наращивая качество
	for(Quality = startQuality; Quality > 0; Quality /= 2)
	{
		// первый этап не прерывать
		if(Quality == startQuality)
		{
			scene->Render(this, RT::Scene::SharedCallback(new ::Callback<false>(this)), Quality);

			if(Dirty)
				return;
		}
		else
		{
			// в более высоком качестве рисовать не обязательно, можно прерваться не дорендерив
			if(!scene->Render(this, RT::Scene::SharedCallback(new ::Callback<true>(this)), Quality))
				return;
		}
	}

	if(Running && !Dirty)
	{
		const int elapsed = static_cast<int>((GetTime() - startTime) * 1000);
		std::cout<<"Render completed after "<<elapsed<<" ms."<<std::endl;
		Rendered = true;
	}
}

void RTDemoApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();

		if(sym == SDLK_PRINT)
			MakeScreenshot();
	}
}

RTDemoApplication::~RTDemoApplication()
{

}

