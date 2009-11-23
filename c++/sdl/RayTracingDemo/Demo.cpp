#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <SDL.h>
#include <sdlapplication/Affine.h>
#include <Camera.h>
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

const double RTDemoApplication::MovementSpeed = 100.0;
const double RTDemoApplication::RotationSpeed = 1.0;

RTDemoApplication::RTDemoApplication() : 
	// Наблюдатель находится перед экраном на расстоянии 1000 пикселов
	scene(new RT::Scene()),
	container(new RT::CompoundObject()),
	camera(new RT::Camera(ScreenWidth, ScreenHeight, 2 * atan(ScreenWidth / 2000.0), 2 * atan(ScreenHeight / 2000.0))),
	Center(Vector3DByCoords(ScreenWidth / 2 + 0.1, 200.1, 400.1)),
	Rendered(false), Dirty(false)
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SetCaption("Ray Tracing Demo");


	// добавить в сцену камеру
	scene->SetCamera(camera);


	// добавить в сцену источник света, типа лампа сверху
	RT::Scene::SharedLight light1(new RT::Light(Vector3DByCoords(ScreenWidth / 2, 3000, -1000) + Center, RealColor(Palette::White)));
	scene->AddLight(light1);

	// а также рассеянное освещение
	scene->SetAmbient(static_cast<RealColor>(Palette::White) * 0.00000002);

	// а также добавить лампу в контейнер как невидимый объект, для того чтобы при вращении контейнера источник тоже двигался
	container->Add(RT::CompoundObject::SharedObject(new RT::Invisible(light1)));
	

	const RT::Material::SharedTexture checkertex(new RT::Texture("Textures/board.bmp"));

	RT::Material checkermat;
	checkermat.SetTexture(checkertex, Vector2DByCoords(0, 0), Vector2DByCoords(0.006, 0), Vector2DByCoords(0, 0.006));


	// наполняем контейнер чем-то

	RT::CompoundObject::SharedObject c(new RT::Sphere(Center, 200, static_cast<RealColor>(Palette::Red)));

	RT::CompoundObject::SharedObject p(new RT::Plane(Vector000, Vector3DByCoords(1, 0, 0), \
		Vector3DByCoords(0, 0, 1), checkermat));

	container->Add(c);
	container->Add(p);


	// добавляем контейнер в сцену
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
	os<<"Camera position: "<<std::setprecision(0)<<camera->GetPosition()<<"; ";
	os<<"direction: "<<std::setprecision(2)<<camera->GetDirection()<<". ";
	os<<"Step: "<<Step<<"; ";
	os<<"extra: "<<extra<<". ";
	os<<"Rendered: "<<static_cast<int>(percent)<<"%.";

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
	if(isPressed(SDLK_RIGHT) || isPressed(SDLK_d))
	{
		camera->RotateHorizontal(-RotationSpeed * dt);
		Dirty = true;
	}

	if(isPressed(SDLK_LEFT) || isPressed(SDLK_a))
	{
		camera->RotateHorizontal(RotationSpeed * dt);
		Dirty = true;
	}

	if(isPressed(SDLK_UP) || isPressed(SDLK_w))
	{
		camera->MoveForward(MovementSpeed * dt);
		Dirty = true;
	}

	if(isPressed(SDLK_DOWN) || isPressed(SDLK_s))
	{
		camera->MoveForward(-MovementSpeed * dt);
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

