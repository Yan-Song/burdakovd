#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>
#include "color.h"
#include "Vector.h"
#include <cmath>

const double Pi = acos(-1.0);

template<class T>
inline T min(const T& x, const T& y)
{
    return x > y ? y : x;
}

class SDLApplication
{
public:
    SDLApplication();
	static void LockSurface(SDL_Surface* surface);
	static void UnlockSurface(SDL_Surface* surface);
	static void DrawPixel(SDL_Surface *surface, const int x, const int y, const Color& color);
    static void DrawPixel(SDL_Surface *surface, const Point& point, const Color& color);
    static int Rand(int x);
    static int Rand(int x, int y);
	void Run(); // �������� ����� ������ ���� ���, ����� �������� ���� ������� �� ����� ������ Stop()
	virtual ~SDLApplication(); // ����������

protected:
	SDL_Surface* Screen;
	void Stop(); // ���������� ������� ������
	virtual void ProcessEvents(); // ���������� ���� ������������
	virtual void ProcessEvent(SDL_Event Event) = 0;
	virtual void Main() = 0; // �������� ������
	virtual void Render() = 0; // ������� �� ����� ������� ��������
	void InitializeSDL(int ScreenHeight, int ScreenWidth, int ColorDepth, int SDLflags); // ���������������� ���������� SDL
	long long frames;

private:
	bool Running;
};

#endif
