#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>
#include "color.h"
#include "Vector.h"
#include <cmath>
#include "utils.h"
#include <list>

struct FrameInfo
{
	// �������� clock()
	long long cclock;
	// clock() - previous clock();
	long long dclock;

	FrameInfo(long long c, long long d) : cclock(c), dclock(d)
	{
	};
};

typedef std::list<FrameInfo> FrameInfoList;

class SDLApplication
{
public:
	SDLApplication();
	void Lock() const ; // ������������� ����� ����� ����� ���� ��������
	void Unlock() const ; // �������������� �����
	void Flip() const ; // SDL_Flip
	// ���������� ���������, ����������� ���� �������� (X - ������, Y - ����)
	void DrawPixel(const int x, const int y, const Color& color) const ;
	void DrawPixel(const ScreenPoint& point, const Color& color) const ;
	// ���������� ����������� �������������
	void FillRectangle(const ScreenPoint& LeftTop, const ScreenPoint& RightBottom, const Color& color) const;
	// �������� �����
	void ClearScreen(const Color& color = Palette::Black) const;
	
	// ����� �� ������������� [0, x)
	static int Rand(int x);
	// �� ������� [x, y]
	static int Rand(int x, int y);
	void Run(); // �������� ����� ������ ���� ���, ����� �������� ���� ������� �� ����� ������ Stop()
	virtual ~SDLApplication(); // ����������

protected:
	SDL_Surface* Screen;
	void Stop(); // ���������� ������� ������
	virtual void ProcessEvents(); // ���������� ���� ������������
	virtual void ProcessEvent(SDL_Event Event) = 0;
	virtual void Main() = 0; // �������� ������
	virtual void InitialRender() {};
	virtual void Render() = 0; // ������� �� ����� ������� ��������
	void InitializeSDL(int ScreenHeight, int ScreenWidth, int ColorDepth, int SDLflags); // ���������������� ���������� SDL
	// ���������� ������ �����
	long long frames;
	// ���������� ������ �� ��������� �������
	inline int FPS() const
	{
		return stats.size();
	}
	// ����������� dt �� ��������� �������, ��
	int dtMin() const;
	// ������� dt �� ��������� �������, ��
	int dtAvg() const;
	// ������������ dt �� ��������� �������, ��
	int dtMax() const;
	// �����, ��������� � ����������� �����, ���.
	double dt;
	// �������� dt, FPS � ������ ����������
	void UpdateStats();
	
	Uint8* KeyState;

private:
	bool Running;
	// ������ ����������
	SDLApplication(const SDLApplication&) {};
	SDLApplication& operator=(const SDLApplication&) {};
	inline Uint32 MapColor(const Color& rgb) const
	{
		return SDL_MapRGB(Screen->format, static_cast<Uint8>(rgb.R), static_cast<Uint8>(rgb.G), static_cast<Uint8>(rgb.B));
	}
	long long lastClock;
	// ���������� �� ��������� �������
	FrameInfoList stats;
};

#endif