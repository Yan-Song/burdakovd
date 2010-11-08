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

const double RTDemoApplication::MovementSpeed = 1000.0;
const double RTDemoApplication::RotationSpeed = 1.0;
const double RTDemoApplication::MouseSensitivity = 0.002;

RTDemoApplication::RTDemoApplication() : 
	scene(new RT::Scene()),
	container(new RT::CompoundObject()),
	camera(new RT::Camera(ScreenWidth, ScreenHeight, 2 * atan(ScreenWidth / 1200.0), 2 * atan(ScreenHeight / 1200.0))),
	Center(Vector3DByCoords(ScreenWidth / 2, 0, 400)),
	Rendered(false), Dirty(false)
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SetCaption("Ray Tracing Demo");


	// добавить в сцену камеру
	scene->SetCamera(camera);


	// добавить в сцену источник света, типа лампа сверху
	RT::Scene::SharedLight light1(new RT::Light(Vector3DByCoords(0, 2000, 2000), RealColor(Palette::White)));
	scene->AddLight(light1);

	// а также рассеянное освещение
	scene->SetAmbient(static_cast<RealColor>(Palette::White) * 0.00000003);

	// а также добавить лампу в контейнер как невидимый объект, для того чтобы при вращении контейнера источник тоже двигался
	container->Add(RT::CompoundObject::SharedObject(new RT::Invisible(light1)));
	
	const double R = 300.0;
	const double PlaneReflection = 0.0;

	RT::Material checkermat;
	const RT::Material::SharedTexture checkertex(new RT::Texture("Textures/grass.bmp"));
	checkermat.SetTexture(checkertex, Vector2DByCoords(0, 0), Vector2DByCoords(1, 0), Vector2DByCoords(0, 1));
	checkermat.SetReflection(PlaneReflection);

	// наполняем контейнер чем-то

	RT::Material RedMaterial(static_cast<RealColor>(Palette::Red));
	RedMaterial.SetReflection(0.3);

	RT::Material GreenMaterial(static_cast<RealColor>(Palette::Green));
	GreenMaterial.SetReflection(0.5);

	RT::Material BlueMaterial(static_cast<RealColor>(Palette::Blue));
	BlueMaterial.SetReflection(0.7);

	RT::Material AzerothMaterial;
	RT::Material::SharedTexture az(new RT::Texture("Textures/azeroth.bmp"));
	AzerothMaterial.SetTexture(az, Vector2DByCoords(0, 0), Vector2DByCoords(az->GetWidth() / 2.0 / Pi / R, 0), Vector2DByCoords(0, -az->GetHeight() / Pi / R));
	AzerothMaterial.SetReflection(0.0);

	RT::Material MiracleMaterial(static_cast<RealColor>(Palette::Gray));
	MiracleMaterial.SetReflection(0.99);

	RT::CompoundObject::SharedObject rs(new RT::Sphere(Vector3DByCoords(-700, R, -200), R, RedMaterial));
	RT::CompoundObject::SharedObject gs(new RT::Sphere(Vector3DByCoords(0, R, -100), R, GreenMaterial));
	RT::CompoundObject::SharedObject bs(new RT::Sphere(Vector3DByCoords(700, R, 0), R, BlueMaterial));
	Vector3D aCenter = Vector3DByCoords(1400, R, 100);
	RT::CompoundObject::SharedObject as(new RT::Sphere(aCenter, R, AzerothMaterial));
	as->Rotate(Affine::X, aCenter, Pi / 2);
	RT::CompoundObject::SharedObject ms(new RT::Sphere(Vector3DByCoords(2100, R, 200), R, MiracleMaterial));

	RT::CompoundObject::SharedObject p(new RT::Plane(Vector000, Vector3DByCoords(1, 0, 0), \
		Vector3DByCoords(0, 0, 1), checkermat));

	container->Add(rs);
	container->Add(gs);
	container->Add(bs);
	container->Add(as);
	container->Add(ms);
	container->Add(p);

	// добавляем контейнер в сцену
	scene->Add(container);

	camera->Locate(Vector3DByCoords(900, 400, 3100));
	camera->PickTarget(Vector3DByCoords(700, 0, 0));
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
	os<<"Camera position: "<<std::setprecision(0)<<std::fixed<<camera->GetPosition()<<"; ";
	os<<"direction: "<<std::setprecision(2)<<std::fixed<<camera->GetDirection()<<". ";
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

	// вперёд можно идти стрелкой, w, или  зажав среднюю кнопку мыши
	if(isPressed(SDLK_UP) || isPressed(SDLK_w) || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MMASK))
	{
		camera->MoveForward(MovementSpeed * dt);
		Dirty = true;
	}

	if(isPressed(SDLK_DOWN) || isPressed(SDLK_s))
	{
		camera->MoveForward(-MovementSpeed * dt);
		Dirty = true;
	}

	if(isPressed(SDLK_SPACE))
	{
		camera->Move(Vector3DByCoords(0, MovementSpeed * dt * 0.2, 0));
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

	scene->SetMinimumRayPower(1.0);

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
			{
				scene->SetMinimumRayPower(0.001);

				if(!scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, true, Step, 2)), Step, true, 2))
					return;

				if(!scene->Render(this, RT::Scene::SharedCallback(new ::Callback(this, true, Step, 4)), Step, true, 4))
					return;
			}
		}
	}

	if(Running && !Dirty)
	{
		const int elapsed = static_cast<int>((GetTime() - startTime) * 1000);
		std::cout<<"Render completed after "<<elapsed<<" ms."<<std::endl;
		Rendered = true;
	}
}

void RTDemoApplication::ProcessEvent(const SDL_Event& Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();

		if(sym == SDLK_PRINT)
			MakeScreenshot();
	}

	if(Event.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_ShowCursor(false);
		SDL_WM_GrabInput(SDL_GRAB_ON);
	}

	if(Event.type == SDL_MOUSEBUTTONUP)
	{
		SDL_ShowCursor(true);
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	}

	if(Event.type == SDL_MOUSEMOTION)
	{	
		// вращать камеру мышью можно с зажатой правой либо левой кнопкой
		if(Event.motion.state & (SDL_BUTTON_LMASK | SDL_BUTTON_RMASK))
		{
			camera->RotateHorizontal(- static_cast<double>(Event.motion.xrel) * MouseSensitivity);
			camera->RotateVertical(- static_cast<double>(Event.motion.yrel) * MouseSensitivity);

			// а это нужно чтоб камера выровняла горизонт, так как крутя мышкой можно наклонить камеру по третmей оси, что не нужно
			camera->SetDirection(camera->GetDirection());

			Dirty = true;
		}
	}
}

RTDemoApplication::~RTDemoApplication()
{

}

