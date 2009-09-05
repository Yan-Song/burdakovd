#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>

class SDLApplication
{
public:
	void Run(); // вызывать извне класса один раз, будет работать пока изнутри не будет вызван Stop()
	virtual ~SDLApplication(); // деструктор

protected:
	void Stop(); // вызывается изнутри класса
	virtual void ProcessEvents(); // обработать ввод пользователя
	virtual void ProcessEvent(SDL_Event Event) = 0;
	virtual void Main() = 0; // основная логика
	virtual void Render() = 0; // вывести на экран текущую ситуацию
	void InitializeSDL(int ScreenWidth, int ScreenHeight, int ColorDepth, int SDLflags); // инициализировать библиотеку SDL
	void LockSurface(SDL_Surface* surface);
	void UnlockSurface(SDL_Surface* surface);
	void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 R, Uint8 G, Uint8 B);
	SDL_Surface* Screen;
	long long frames;

private:
	bool Running;
};

#endif
