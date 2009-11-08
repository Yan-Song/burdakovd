#include "Demo.h"
#include "SDL.h"
#include "Sphere.h"
#include "Ray.h"
#include <iostream>

// x - вправо
// y - вверх
// z - вперед

RTDemoApplication::RTDemoApplication()
{
	const int SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT || SDL_HWSURFACE;

	InitializeSDL(ScreenHeight, ScreenWidth, 0, SDLflags);

	SDL_WM_SetCaption("Ray Tracing Demo", NULL);
}

void RTDemoApplication::InitialRender()
{
	Lock();

	ClearScreen();

	const RT::Sphere sphere(Vector3DByCoords(320, 240, 500), 100);
	
	for(int x = 0; x < ScreenWidth; ++x)
		for(int y = 0; y < ScreenHeight; ++y)
		{
			const RT::Ray ray(RT::NormalizedVector3D(0, 0, 1), Vector3DByCoords(x, y, 0));

			if(sphere.CheckIntersection(ray))
				RawDrawPixel(x, y, Palette::White);
		}

	Unlock();
	Flip();

	std::cout<<"Initial render complete"<<std::endl;
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

