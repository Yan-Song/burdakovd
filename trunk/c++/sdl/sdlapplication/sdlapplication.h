#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>

class SDLApplication
{
public:
	SDLApplication(); // конструктор
	void Run(); // вызывать извне класса один раз, будет работать пока изнутри не будет вызван Stop()
	virtual ~SDLApplication(); // деструктор

protected:
	void Stop(); // вызывается изнутри класса
	virtual void ProcessEvents(); // обработать ввод пользователя
	virtual void Main(); // основная логика
	virtual void Render(); // вывести на экран текущую ситуацию
	void InitializeSDL(int ScreenWidth, int ScreenHeight, int ColorDepth); // инициализировать библиотеку SDL

private:
	bool Running;
	SDL_Surface* Screen;
};

#endif
