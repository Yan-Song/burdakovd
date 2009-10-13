#include <SDL.h>
#include "sdlapplication.h"
#include "SDLException.h"
#include <ctime>
#include <iostream>
#include "Timer.h"

SDLApplication::SDLApplication()
{
    srand(static_cast<unsigned int>(time(NULL)));
	std::cout<<"Random number generator initialized"<<std::endl;
	dt = 0;
	frames = 0;
	lastTime = GetTime();
}

void SDLApplication::UpdateStats()
{
	double ctime = GetTime();
	dt = ctime - lastTime;
	lastTime = ctime;
	
	// добавляем статистику по текущему кадру
	stats.push_back(FrameInfo(ctime, dt));

	// удаляем статистику старее одной секунды
	while(!stats.empty() && ctime - stats.front().ctime > 1)
		stats.pop_front();

	++frames;

}

int SDLApplication::dtAvg() const
{
	if(stats.size() > 0)
	{
		double sum = 0;
		
		for(FrameInfoList::const_iterator it = stats.begin(); it != stats.end(); ++it)
			sum += it->dt;

		return static_cast<int>(sum * 1000 / stats.size());
	}
	else
	{
		return 0;
	}
}

int SDLApplication::dtMax() const
{
	if(stats.size() > 0)
	{
		double ans = 0;
		
		for(FrameInfoList::const_iterator it = stats.begin(); it != stats.end(); ++it)
			if(it->dt > ans)
				ans = it->dt;

		return static_cast<int>(ans * 1000);
	}
	else
	{
		return 0;
	}
}

int SDLApplication::dtMin() const
{
	if(stats.size() > 0)
	{
		double ans = 86400; // сутки
		
		for(FrameInfoList::const_iterator it = stats.begin(); it != stats.end(); ++it)
			if(it->dt < ans)
				ans = it->dt;

		return static_cast<int>(ans * 1000);
	}
	else
	{
		return 0;
	}
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

	KeyState = SDL_GetKeyState(NULL);

	timer.Reset();

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
	Running = true;

	std::cout<<"Run()"<<std::endl;

	InitialRender();

	while(Running)
	{
		UpdateStats();
		ProcessEvents();
		Main();
		Render();
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

void SDLApplication::DrawPixel(const ScreenPoint& point, const Color& color) const
{
    DrawPixel(point[0], point[1], color);
}

// http://plg.lrn.ru/doc/sdl/lesson1.html
void SDLApplication::DrawPixel(const int x, const int y, const Color& rgb) const
{
    if(x < 0  || x >= Screen->w || y < 0 || y >= Screen->h) return; // out of bounds

	Uint32 color = MapColor(rgb);

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

void SDLApplication::FillRectangle(const ScreenPoint& LeftTop, const ScreenPoint& RightBottom, const Color& color) const
{
	SDL_Rect rect;
	rect.x = static_cast<Sint16>(LeftTop[0]);
	rect.y = static_cast<Sint16>(LeftTop[1]);
	rect.w = static_cast<Uint16>(RightBottom[0] - rect.x);
	rect.h = static_cast<Uint16>(RightBottom[1] - rect.y);
	SDL_FillRect(Screen, &rect, MapColor(color));
}

void SDLApplication::ClearScreen(const Color& color) const
{
	ScreenPoint LeftTop, RightBottom;
	RightBottom[0] = Screen->w;
	RightBottom[1] = Screen->h;
	FillRectangle(LeftTop, RightBottom, color);
}