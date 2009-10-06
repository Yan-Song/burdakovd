#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>
#include "color.h"
#include "Vector.h"
#include <vector>
#include <cmath>
#include <map>

typedef std::pair<int, int> pii;

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
	void LockSurface() const;
	void UnlockSurface() const;
	void Flip() const;
	void DrawPixel(const int x, const int y, const Color& color) const;
	void DrawPixel(const Point& point, const Color& color) const;
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
	// ������ ����������
	SDLApplication(const SDLApplication& a) {};
	SDLApplication& operator=(const SDLApplication& a) {};
};

#endif
