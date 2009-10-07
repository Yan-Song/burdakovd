#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>
#include "color.h"
#include "Vector.h"
#include <cmath>
#include "utils.h"

class SDLApplication
{
public:
	SDLApplication();
	void Lock() const ; // Заблокировать экран чтобы можно было рисовать
	void Unlock() const ; // Разблокировать экран
	void Flip() const ; // SDL_Flip
	// координаты Декартовы, направление осей экранное (X - вправо, Y - вниз)
	void DrawPixel(const int x, const int y, const Color& color) const ;
	void DrawPixel(const ScreenPoint& point, const Color& color) const ;
	// нарисовать закрашенный прямоугольник
	void FillRectangle(const ScreenPoint& LeftTop, const ScreenPoint& RightBottom, const Color& color) const;
	// очистить экран
	void ClearScreen(const Color& color = Palette::Black) const;
	
	// число из полуинтервала [0, x)
	static int Rand(int x);
	// из отрезка [x, y]
	static int Rand(int x, int y);
	void Run(); // вызывать извне класса один раз, будет работать пока изнутри не будет вызван Stop()
	virtual ~SDLApplication(); // деструктор

protected:
	SDL_Surface* Screen;
	void Stop(); // вызывается изнутри класса
	virtual void ProcessEvents(); // обработать ввод пользователя
	virtual void ProcessEvent(SDL_Event Event) = 0;
	virtual void Main() = 0; // основная логика
	virtual void InitialRender() {};
	virtual void Render() = 0; // вывести на экран текущую ситуацию
	void InitializeSDL(int ScreenHeight, int ScreenWidth, int ColorDepth, int SDLflags); // инициализировать библиотеку SDL
	long long frames;

private:
	bool Running;
	// нельзя копировать
	SDLApplication(const SDLApplication&) {};
	SDLApplication& operator=(const SDLApplication&) {};
	inline Uint32 MapColor(const Color& rgb) const
	{
		return SDL_MapRGB(Screen->format, static_cast<Uint8>(rgb.R), static_cast<Uint8>(rgb.G), static_cast<Uint8>(rgb.B));
	}
};

#endif
