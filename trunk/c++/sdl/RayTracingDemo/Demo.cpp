#include <iostream>
#include <sstream>
#include <SDL.h>
#include <sdlapplication/Affine.h>
#include <CompoundObject.h>
#include <Cube.h>
#include <Frustum.h>
#include <IntersectionResult.h>
#include <Invisible.h>
#include <Light.h>
#include <Material.h>
#include <Plane.h>
#include <Ray.h>
#include <Scene.h>
#include <SierpinskiPyramide.h>
#include <Sphere.h>
#include <Tetragon.h>
#include <Texture.h>
#include <Triangle.h>
#include "Demo.h"

// x - вправо
// y - вверх
// z - вперед

RTDemoApplication::RTDemoApplication() : 
	// Наблюдатель находится перед экраном на расстоянии 1000 пикселов
	scene(new RT::Scene(Vector3DByCoords(ScreenWidth / 2 + 0.3, ScreenHeight / 2 + 107, -1013))),
	container(new RT::CompoundObject()),
	Center(Vector3DByCoords(ScreenWidth / 2 + 0.1, 200.1, 400.1)),
	Rendered(false), Dirty(false)
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SDL_WM_SetCaption("Ray Tracing Demo", NULL);

	// добавить в сцену источник света, типа лампа сверху
	RT::Scene::SharedLight light1(new RT::Light(Vector3DByCoords(ScreenWidth / 2, 3000, -1000) + Center, RealColor(Palette::White)));
	scene->AddLight(light1);

	// а также рассеянное освещение
	scene->SetAmbient(static_cast<RealColor>(Palette::White) * 0.00000001);

	// а также добавить лампу в контейнер как невидимый объект, для того чтобы при вращении контейнера источник тоже двигался
	container->Add(RT::CompoundObject::SharedObject(new RT::Invisible(light1)));
	
	//const double R = 300;

	const RT::Material::SharedTexture checkertex(new RT::Texture("Textures/board.bmp"));

	RT::Material checkermat;
	checkermat.SetTexture(checkertex, Vector2DByCoords(0, 0), Vector2DByCoords(0.006, 0), Vector2DByCoords(0, 0.006));

	// наполняем контейнер чем-то
	//RT::CompoundObject::SharedObject c(new RT::Cube(Center, R, woodmat));
	RT::CompoundObject::SharedObject p(new RT::Plane(Vector000, Vector3DByCoords(1, 0, 0), \
		Vector3DByCoords(0, 0, 1), checkermat));

	//container->Add(c);
	container->Add(p);

	// добавляем его в сцену
	scene->Add(container);
}

class Callback : public RT::Scene::ICallback
{
private:
	RTDemoApplication* app;
	bool AllowBreak;
	unsigned int Step;
	unsigned int extra;

	Callback(const Callback& );
	Callback operator=(const Callback&);

public:
	Callback(RTDemoApplication* const _app, const bool _AllowBreak, const unsigned int _Quality, \
		const unsigned int _extra) :
	app(_app), AllowBreak(_AllowBreak), Step(_Quality), extra(_extra) {}

	virtual bool call(const double percent)
	{
		if(AllowBreak)
			return app->Callback(percent, true, Step, extra);
		else
		{
			app->Callback(percent, false, Step, extra);
			return false;
		}
	}
};

bool RTDemoApplication::Callback(const double percent, const bool AllowBreak, const unsigned int Step, \
								 const unsigned int extra)
{
	// вывести прогресс
	std::ostringstream os;
	os<<"Ray Tracing Demo. ";
	os<<"Step: "<<Step;
	os<<"; extra: "<<extra;
	os<<". Rendered: "<<static_cast<int>(percent)<<"%.";
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

	const unsigned int startStep = 16;

	// рисовать, постепенно наращивая качество
	for(unsigned int Step = startStep; Step > 0; Step /= 2)
	{
		// первый этап не прерывать
		if(Step == startStep)
		{
			scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, false, Step, 1)), Step);

			if(Dirty)
				return;
		}
		else
		{
			// в более высоком качестве рисовать не обязательно, можно прерваться не дорендерив
			if(!scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, true, Step, 1)), Step))
				return;

			// если шаг == 1, то можно ещё нарисовать со сглаживанием
			if(Step == 1)
				if(!scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, true, Step, 2)), Step, true, 2))
					return;

			if(Step == 1)
				if(!scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, true, Step, 4)), Step, true, 4))
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

