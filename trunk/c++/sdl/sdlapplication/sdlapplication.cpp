#include <SDL.h>
#include "sdlapplication.h"
#include "SDLException.h"
#include <ctime>
#include <iostream>

SDLApplication::SDLApplication()
{
    srand(static_cast<unsigned int>(time(NULL)));
	std::cout<<"Random number generator initialized"<<std::endl;
}

void SDLApplication::InitializeSDL(int ScreenHeight, int ScreenWidth, int ColorDepth, int SDLflags)
{
	// Load SDL
	SDLCheck(SDL_Init(SDL_INIT_EVERYTHING));

	Screen = SDL_SetVideoMode(ScreenWidth, ScreenHeight, ColorDepth, SDLflags);
	if (!Screen)
	{
		throw new SDLException();
	}

	std::cout<<"SDL initialized"<<std::endl;
}

SDLApplication::~SDLApplication()
{
	SDL_Quit();
	std::cout<<"SDL unloaded"<<std::endl;
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

	std::cout<<"Run()"<<std::endl;

	while(Running)
	{
		ProcessEvents();
		Main();
		Render();
		++frames;
	}

	std::cout<<"Stopped"<<std::endl;
}

void SDLApplication::Stop()
{
	Running = false;
	std::cout<<"Stop()"<<std::endl;
}

void SDLApplication::Lock() const
{
	if(SDL_MUSTLOCK(Screen))
		SDLCheck(SDL_LockSurface(Screen));
}

void SDLApplication::Unlock() const
{
	if(SDL_MUSTLOCK(Screen))
		SDL_UnlockSurface(Screen);
}

void SDLApplication::Flip() const
{
	SDLCheck(SDL_Flip(Screen));
}

void SDLApplication::DrawPixel(const Point& point, const Color& color) const
{
    DrawPixel(static_cast<int>(point.X()), static_cast<int>(point.Y()), color);
}

// http://plg.lrn.ru/doc/sdl/lesson1.html
void SDLApplication::DrawPixel(const int x, const int y, const Color& rgb) const
{
    if(x < 0  || x >= Screen->w || y < 0 || y >= Screen->h) return; // out of bounds

	Uint32 color = SDL_MapRGB(Screen->format, static_cast<Uint8>(rgb.r), static_cast<Uint8>(rgb.g), static_cast<Uint8>(rgb.b)); 
	switch (Screen->format->BytesPerPixel){ 
	   case 1:  // Assuming 8-bpp 
	   { 
		 Uint8 *bufp; 
		 bufp = (Uint8 *)Screen->pixels + y*Screen->pitch + x; *bufp = static_cast<Uint8>(color); 
	   } break; 
	   case 2: // Probably 15-bpp or 16-bpp 
	   { 
		 Uint16 *bufp; 
		 bufp = (Uint16 *)Screen->pixels + y*Screen->pitch/2 + x; *bufp = static_cast<Uint16>(color);
	   } break; 
	   case 3: // Slow 24-bpp mode, usually not used 
	   { 
		 Uint8 *bufp; 
		 bufp = (Uint8 *)Screen->pixels + y*Screen->pitch + x * 3; 
		 #if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
		 { 
		   bufp[0] = static_cast<Uint8>(color); 
		   bufp[1] = static_cast<Uint8>(color >> 8);
		   bufp[2] = static_cast<Uint8>(color >> 16); 
		 }
		 #else
		 { 
		   bufp[2] = color; 
		   bufp[1] = color >> 8; 
		   bufp[0] = color >> 16; 
		 } 
		#endif
	   } break; 
	   case 4: // Probably 32-bpp 
	   { 
		 Uint32 *bufp; 
		 bufp = (Uint32 *)Screen->pixels + y*Screen->pitch/4 + x; 
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
