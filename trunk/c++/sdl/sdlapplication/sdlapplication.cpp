#include <SDL.h>
#include "sdlapplication.h"
#include <ctime>

SDLApplication::SDLApplication()
{
    srand(time(NULL));
}

void SDLApplication::InitializeSDL(Point ScreenSize, int ColorDepth, int SDLflags)
{
	// Load SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	Screen = SDL_SetVideoMode(ScreenSize.x, ScreenSize.y, ColorDepth, SDLflags);
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

void SDLApplication::ProcessEvents()
{
	SDL_Event Event;

	while(SDL_PollEvent(&Event))
		if(Event.type == SDL_QUIT)
			Stop();
		else
			ProcessEvent(Event);
}

void SDLApplication::Run()
{
	frames = 0;
	Running = true;

	printf("Run()\n");

	while(Running)
	{
		ProcessEvents();
		Main();
		Render();
		++frames;
	}

	printf("Stopped\n");
}

void SDLApplication::Stop()
{
	Running = false;
	printf("Stop()\n");
}

void SDLApplication::LockSurface(SDL_Surface* surface)
{
	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
}

void SDLApplication::UnlockSurface(SDL_Surface* surface)
{
	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}

// http://plg.lrn.ru/doc/sdl/lesson1.html
void SDLApplication::DrawPixel(SDL_Surface *surface, const Point& point, const Color& rgb)
{
	int R = rgb.r, G = rgb.g, B = rgb.b;
	int x = point.x, y = point.y;
    if(x < 0  || x >= surface->w || y < 0 || y >= surface->h) return;

	Uint32 color = SDL_MapRGB(surface->format, R, G, B); 
	switch (surface->format->BytesPerPixel){ 
	   case 1:  // Assuming 8-bpp 
	   { 
		 Uint8 *bufp; 
		 bufp = (Uint8 *)surface->pixels + y*surface->pitch + x; *bufp = color; 
	   } break; 
	   case 2: // Probably 15-bpp or 16-bpp 
	   { 
		 Uint16 *bufp; 
		 bufp = (Uint16 *)surface->pixels + y*surface->pitch/2 + x; *bufp = color;
	   } break; 
	   case 3: // Slow 24-bpp mode, usually not used 
	   { 
		 Uint8 *bufp; 
		 bufp = (Uint8 *)surface->pixels + y*surface->pitch + x * 3; 
		 if(SDL_BYTEORDER == SDL_LIL_ENDIAN){ 
		   bufp[0] = color; 
		   bufp[1] = color >> 8;
		   bufp[2] = color >> 16; 
		 }else{ 
		   bufp[2] = color; 
		   bufp[1] = color >> 8; 
		   bufp[0] = color >> 16; 
		 } 
	   } break; 
	   case 4: // Probably 32-bpp 
	   { 
		 Uint32 *bufp; 
		 bufp = (Uint32 *)surface->pixels + y*surface->pitch/4 + x; 
		 *bufp = color; 
	   } break; 
	 } 
}

// исключая x
int SDLApplication::Rand(int x)
{
    return rand() % x;
}

// [x, y]
int SDLApplication::Rand(int x, int y)
{
    return x > y ? Rand(y, x) : x + Rand(y - x + 1);
}
