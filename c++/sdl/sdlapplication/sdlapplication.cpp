#include <SDL.h>
#include "sdlapplication.h"

SDLApplication::SDLApplication(): Running(false)
{
	InitializeSDL(640, 480, 8);
}

void SDLApplication::InitializeSDL(int ScreenWidth, int ScreenHeight, int ColorDepth)
{
	// Load SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	atexit(SDL_Quit); // Clean it up nicely :)

	Screen = SDL_SetVideoMode(ScreenWidth, ScreenHeight, ColorDepth, SDL_DOUBLEBUF);
	if (!Screen)
	{
		fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
		exit(1);
	}

	printf("SDL initialized\n");
}

SDLApplication::~SDLApplication()
{
	SDL_Quit();
	printf("SDL unloaded\n");
}

void SDLApplication::Main()
{
}

void SDLApplication::ProcessEvents()
{
}

void SDLApplication::Render()
{
}

void SDLApplication::Run()
{
	Running = true;

	printf("Run()\n");

	while(Running)
	{
		ProcessEvents();
		Main();
		Render();
	}

	printf("Stopped\n");
}

void SDLApplication::Stop()
{
	Running = false;
	printf("Stop()\n");
}
