#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>
#include "color.h"
#include "Vector.h"

class SDLApplication
{
public:
    SDLApplication();
	static void LockSurface(SDL_Surface* surface);
	static void UnlockSurface(SDL_Surface* surface);
	static void DrawPixel(SDL_Surface *surface, const Point& point, const Color& color);
    static int Rand(int x);
    static int Rand(int x, int y);
	void Run(); // вызывать извне класса один раз, будет работать пока изнутри не будет вызван Stop()
	virtual ~SDLApplication(); // деструктор

protected:
	SDL_Surface* Screen;
	void Stop(); // вызывается изнутри класса
	virtual void ProcessEvents(); // обработать ввод пользователя
	virtual void ProcessEvent(SDL_Event Event) = 0;
	virtual void Main() = 0; // основная логика
	virtual void Render() = 0; // вывести на экран текущую ситуацию
	void InitializeSDL(Point ScreenSize, int ColorDepth, int SDLflags); // инициализировать библиотеку SDL
	long long frames;

private:
	bool Running;
};

#endif
