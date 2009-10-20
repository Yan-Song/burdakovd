#include "Mandelbrot.h"
#include <ctime>
#include <iostream>

Mandelbrot::Mandelbrot(void)
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Mandelbrot", NULL);
	lasttime = time(NULL);
	lastframes = 0;
	k = 0.01;
	bx = by = 0;
	needReDraw = false;
	int ops = 0;
}

Mandelbrot::~Mandelbrot(void)
{
}

void Mandelbrot::DoNavigation()
{
	if(KeyState[SDLK_UP])
	{
		by += 20 * k; // на 20 пикселей
		needReDraw = true;
	}

	if(KeyState[SDLK_DOWN])
	{
		by -= 20 * k; // на 20 пикселей
		needReDraw = true;
	}

	if(KeyState[SDLK_LEFT])
	{
		bx -= 20 * k; // на 20 пикселей
		needReDraw = true;
	}

	if(KeyState[SDLK_RIGHT])
	{
		bx += 20 * k; // на 20 пикселей
		needReDraw = true;
	}

	if(KeyState[SDLK_MINUS])
	{
		bx -= ScreenWidth / 2 * 0.3 * k;
		needReDraw = true;
		by -= ScreenHeight / 2 * 0.3 * k;
		k *= 1.3;
	}

	if(KeyState[SDLK_PLUS] || KeyState[SDLK_EQUALS])
	{
		bx += ScreenWidth / 2 * (1 - 1 / 1.3) * k;
		by += ScreenHeight / 2 * (1 - 1 / 1.3) * k;
		k /= 1.3;
		needReDraw = true;
	}
}

void Mandelbrot::Main()
{
	if(lasttime != time(NULL))
	{
		lasttime = time(NULL);
		std::cout<<"FPS: "<<(frames-lastframes)<<std::endl;
		lastframes = frames;
	}

	DoNavigation();
}

void Mandelbrot::Render()
{
	// Прорисовываем всё подробнее и подробнее
	for(int depth = 5; ; depth *= 2)
	{

		Lock();

		ClearScreen(Palette::Black);

		for(int x = 0; x < ScreenWidth; ++x)
			for(int y = 0; y < ScreenHeight; ++y)
			{
				Complex c(k * x + bx, k * y + by);
				DrawPixel(x, ScreenHeight - y, GetColor(c, depth));
				if(ops>100000)
				{
					ops = 0;
					ProcessEvents();
					if(needReDraw)
					{
						needReDraw = false;
						goto brk;
					}
				}
			}

		Unlock();
		Flip();
	}

brk: ;
}

void Mandelbrot::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();
	}
	
	needReDraw = true;
}

Color Mandelbrot::GetColor(const Complex &c, int depth)
{
	Complex z = 0;

	for(int ii = 0; ii < depth; ++ii)
	{
		++ops;
		z = z * z + c;
		if( sqr(z.real()) + sqr(z.imag()) > 4 )
		{
			int i = 7 * ii;
			if(i<255)
				return Color(255-i, 255-i, 255-i);
			else if(i<65535)
				return Color(0, 0, 0);
			else
				return Color(0, 0 , 0);
		}
	}

	return Palette::Black;
}
