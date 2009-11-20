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
	scene(new RT::Scene(Vector3DByCoords(ScreenWidth / 2, ScreenHeight / 2 + 100, -1000))),
	container(new RT::CompoundObject()),
	Center(Vector3DByCoords(ScreenWidth / 2 + 0.1, 200.1, 400.1)),
	Rendered(false), Dirty(false)
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SDL_WM_SetCaption("Ray Tracing Demo", NULL);

	RT::Scene::SharedLight light0(new RT::Light(scene->SpectatorPosition, RealColor(Palette::White)));
	scene->AddLight(light0);

	// добавить в сцену источник света, типа лампа сверху
	RT::Scene::SharedLight light1(new RT::Light(Vector3DByCoords(-1070, 1000, -1030) + Center, RealColor(Palette::White)));
	scene->AddLight(light1);

	// и ещё один источник
	RT::Scene::SharedLight light2(new RT::Light(Vector3DByCoords(-1000, 1000, 1100) + Center, RealColor(Palette::White)));
	scene->AddLight(light2);

	// и ещё один источник
	RT::Scene::SharedLight light3(new RT::Light(Vector3DByCoords(1000, 1000, -1100) + Center, RealColor(Palette::White)));
	scene->AddLight(light3);

	// и ещё один источник
	RT::Scene::SharedLight light4(new RT::Light(Vector3DByCoords(1080, 1000, 1000) + Center, RealColor(Palette::White)));
	scene->AddLight(light4);

	// а также рассеянное освещение
	scene->SetAmbient(static_cast<RealColor>(Palette::White) * 0.0000001);

	// а также добавить лампу в контейнер как невидимый объект, для того чтобы при вращении контейнера источник тоже двигался
	container->Add(RT::CompoundObject::SharedObject(new RT::Invisible(light1)));
	container->Add(RT::CompoundObject::SharedObject(new RT::Invisible(light2)));
	container->Add(RT::CompoundObject::SharedObject(new RT::Invisible(light3)));
	container->Add(RT::CompoundObject::SharedObject(new RT::Invisible(light4)));

	const double R = 300;

	const RT::Material::SharedTexture woodtex(new RT::Texture("Textures/wood.bmp"));

	RT::Material woodmat;
	woodmat.SetTexture(woodtex, Vector2DByCoords(0, 0), Vector2DByCoords(1, 0), Vector2DByCoords(0, 1));

	// наполняем контейнер чем-то
	RT::CompoundObject::SharedObject c(new RT::Cube(Center, R, woodmat));
	RT::CompoundObject::SharedObject p(new RT::Plane(Vector000, Vector3DByCoords(1, 0, 0), \
		Vector3DByCoords(0, 0, 1), RealColor(Palette::White)));

	container->Add(c);
	container->Add(p);

	// добавляем его в сцену
	scene->Add(container);
}

class Callback : public RT::Scene::ICallback
{
private:
	RTDemoApplication* app;
	bool AllowBreak;
	unsigned int Quality;

	Callback(const Callback& );
	Callback operator=(const Callback&);

public:
	Callback(RTDemoApplication* const _app, const bool _AllowBreak, const unsigned int _Quality) :
	app(_app), AllowBreak(_AllowBreak), Quality(_Quality) {}

	virtual bool call(const double percent)
	{
		if(AllowBreak)
			return app->Callback(percent, true, Quality);
		else
		{
			app->Callback(percent, false, Quality);
			return false;
		}
	}
};

bool RTDemoApplication::Callback(const double percent, const bool AllowBreak, const unsigned int Quality)
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

	const unsigned int startQuality = 16;

	// рисовать, постепенно наращивая качество
	for(unsigned int Quality = startQuality; Quality > 0; Quality /= 2)
	{
		// первый этап не прерывать
		if(Quality == startQuality)
		{
			scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, false, Quality)), Quality);

			if(Dirty)
				return;
		}
		else
		{
			// в более высоком качестве рисовать не обязательно, можно прерваться не дорендерив
			if(!scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, true, Quality)), Quality))
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

