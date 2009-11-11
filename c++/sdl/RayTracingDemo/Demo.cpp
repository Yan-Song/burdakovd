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
#include "Triangle.h"
#include "Frustum.h"
#include "SierpinskiPyramide.h"

// x - вправо
// y - вверх
// z - вперед

RTDemoApplication::RTDemoApplication() : 
	// Наблюдатель находится перед экраном на расстоянии 1000 пикселов
	scene(RT::shared_ptr<RT::Scene>(new RT::Scene(Vector3DByCoords(ScreenWidth / 2, ScreenHeight / 2, -500)))),
		container(new RT::CompoundObject()),
		Rendered(false), Dirty(false), Center(Vector3DByCoords(ScreenWidth / 2 + 0.1, 200.1, 400.1))
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SDL_WM_SetCaption("Ray Tracing Demo", NULL);

	// наполняем контейнер чем-то
	RT::CompoundObject::SharedObject s = RT::CompoundObject::SharedObject(new RT::SierpinskiPyramide(Center, 700, 10, Palette::Green));

	s->Rotate(Affine::X, Center, - Pi / 2);

	container->Add(s);

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
			return app->Callback(percent, true);
		else
		{
			app->Callback(percent, false);
			return false;
		}
	}
};

bool RTDemoApplication::Callback(const double percent, const bool AllowBreak)
{
	// вывести прогресс
	std::ostringstream os;
	os<<"Ray Tracing Demo. Rendered: "<<static_cast<int>(percent)<<"%. ";
	os<<"Quality: "<<Quality;
	SetCaption(os.str());
	
	if(AllowBreak)
	{
		UpdateStats();
		// обработать ввод пользователя
		ProcessEvents();
		Navigate();
		// прервать процесс если приложение пора закрывать или картинка уже устарела
		return (!(Running)) || Dirty;
	}
	else
	{
		return false;
	}
}

void RTDemoApplication::InitialRender()
{
	ClearScreen();
}

void RTDemoApplication::Navigate()
{
	if(isPressed(SDLK_RIGHT))
	{
		container->Rotate(Affine::Y, Center, dt);
		Dirty = true;
	}

	if(isPressed(SDLK_LEFT))
	{
		container->Rotate(Affine::Y, Center, -dt);
		Dirty = true;
	}

	if(isPressed(SDLK_UP))
	{
		container->Rotate(Affine::X, Center, dt);
		Dirty = true;
	}

	if(isPressed(SDLK_DOWN))
	{
		container->Rotate(Affine::X, Center, -dt);
		Dirty = true;
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

	const int startQuality = 16;

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

