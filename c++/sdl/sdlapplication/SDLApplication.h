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
#include <sstream>
#include <ctime>
#include <iostream>
#include "Shared.h"

struct FrameInfo
{
	double cticks;
	double dt;

	FrameInfo(Uint32 c, double d) : cticks(c), dt(d)
	{
	};
};

typedef std::list<FrameInfo> FrameInfoList;

class SDLApplication
{
public:
	SDLApplication();

	// установить заголовок окна
	void SetCaption(const std::string& text);
	
	void Lock(); // Заблокировать экран чтобы можно было рисовать

	inline bool isLocked() const
	{
		return _locked > 0;
	}
	
	void Unlock(); // Разблокировать экран
	
	void Flip() const ; // SDL_Flip

	// координаты Декартовы, направление осей нормальное (X - вправо, Y - вверх)
	void DrawPixel(const int x, int y, const Color& color);

	// не блокирует экран (предполагается что он уже заблокирован)
	void RawDrawPixel(const int x, int y, const Color& color) const;
	
	void DrawPixel(const ScreenPoint& point, const Color& color);
	
	// нарисовать отрезок
	void DrawSegment(const ScreenPoint& A, const ScreenPoint& B, const Color& color);
	
	// нарисовать закрашенный прямоугольник
	void FillRectangle(const ScreenPoint& A, const ScreenPoint& B, const Color& color) const;
	
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

	inline double GetTicks() const
	{
		return timer.GetTicks();
	}

	inline unsigned int FPS() const
	{
		return static_cast<unsigned int>(stats.size());
	}

	inline bool isPressed(const SDLKey& key) const
	{
		return KeyState[key] != 0;
	}

	inline void MakeScreenshot(const std::string& path) const
	{
		if(isLocked())
		{
			std::cout<<"Failed to make screenshot: Screen is locked"<<std::endl;
		}
		else
		{
			if(SDL_SaveBMP(Screen, path.c_str()) == 0)
				std::cout<<"Screenshot saved to "<<path<<std::endl;
			else
				std::cout<<"Failed to save screenshot to "<<path<<": "<<SDL_GetError()<<std::endl;
		}
	}

	inline void MakeScreenshot()
	{
		std::ostringstream path;

		path<<"./Screenshots/Screenshot-";
		path<<startTime<<"-"<<GetTime();
		path<<".bmp";

		MakeScreenshot(path.str());
	}

	SDL_Surface* Screen;

	virtual ~SDLApplication(); // деструктор

protected:
	void Stop(); // вызывается изнутри класса
	
	virtual void ProcessEvents(); // обработать ввод пользователя
	
	virtual void ProcessEvent(SDL_Event ) {};
	
	virtual void Main() {}; // основная логика
	
	virtual void InitialRender() {};
	
	virtual void Render() {}; // вывести на экран текущую ситуацию
	
	void InitializeSDL(size_t ScreenHeight, size_t ScreenWidth, int ColorDepth, size_t SDLflags); // инициализировать библиотеку SDL
	
	// количество кадров всего
	unsigned int frames;
	
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

	Uint8* KeyState;

	bool Running;

private:
	time_t startTime;
	int _locked;

	// нельзя копировать
	SDLApplication(const SDLApplication&);
	SDLApplication& operator=(const SDLApplication&);
	
	inline Uint32 MapColor(const Color& rgb) const
	{
		assert(rgb.R >= 0 && rgb.B >=0 && rgb.G >= 0 && rgb.R < 256 && rgb.G < 256 && rgb.B < 256);
		return SDL_MapRGB(Screen->format, static_cast<Uint8>(rgb.R), static_cast<Uint8>(rgb.G), static_cast<Uint8>(rgb.B));
	}
	
	// статистика за последнюю секунду
	FrameInfoList stats;
	
	Timer timer, fps;
};

#endif
