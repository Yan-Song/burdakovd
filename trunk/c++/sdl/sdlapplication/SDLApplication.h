#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>
#include "Color.h"
#include "Vector.h"
#include <cmath>
#include "Utils.h"
#include <list>
#include "Timer.h"
#include <string>

struct FrameInfo
{
	double ctime;
	double dt;

	FrameInfo(double c, double d) : ctime(c), dt(d)
	{
	};
};

typedef std::list<FrameInfo> FrameInfoList;

class SDLApplication
{
public:
	SDLApplication();
	void Lock() const ; // Заблокировать экран чтобы можно было рисовать
	void Unlock() const ; // Разблокировать экран
	void Flip() const ; // SDL_Flip
	// координаты Декартовы, направление осей экранное (X - вправо, Y - вниз)
	void DrawPixel(const int x, const int y, const Color& color) const;
	void DrawPixel(const ScreenPoint& point, const Color& color) const;
	// нарисовать отрезок
	void DrawSegment(const ScreenPoint& A, const ScreenPoint& B, const Color& color) const;
	// нарисовать закрашенный прямоугольник
	void FillRectangle(const ScreenPoint& LeftTop, const ScreenPoint& RightBottom, const Color& color) const;
	// очистить экран
	void ClearScreen(const Color& color = Palette::Black) const;
	
	// число из полуинтервала [0, x)
	static int Rand(int x);
	// из отрезка [x, y]
	static int Rand(int x, int y);
	void Run(); // вызывать извне класса один раз, будет работать пока изнутри не будет вызван Stop()
	// время с момента инициализации библиотеки SDL в секундах, точность около 1мс.
	// До вызова InitializeSDL результат вызова функции не определён.
	inline double GetTime() const
	{
		return timer.GetTime();
	}
	inline int FPS() const
	{
		return stats.size();
	}
	inline bool isPressed(const SDLKey key) const
	{
		return KeyState[key] != 0;
	}
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
	// количество кадров всего
	long long frames;
	// количество кадров за последнюю секунду
	
	// минимальный dt за последнюю секунду, мс
	int dtMin() const;
	// средний dt за последнюю секунду, мс
	int dtAvg() const;
	// максимальный dt за последнюю секунду, мс
	int dtMax() const;
	// время, прошедшее с предыдущего кадра, сек.
	double dt;
	// обновить dt, FPS и прочую информацию
	void UpdateStats();
	// установить заголовок окна
	void SetCaption(const std::string& text);

	Uint8* KeyState;

private:
	bool Running;
	// нельзя копировать
	SDLApplication(const SDLApplication&) {};
	SDLApplication& operator=(const SDLApplication&) { return *this; };
	inline Uint32 MapColor(const Color& rgb) const
	{
		return SDL_MapRGB(Screen->format, static_cast<Uint8>(rgb.R), static_cast<Uint8>(rgb.G), static_cast<Uint8>(rgb.B));
	}
	double lastTime;
	// статистика за последнюю секунду
	FrameInfoList stats;
	Timer timer;
};

#endif
