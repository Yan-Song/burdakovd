#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>

class SDLApplication
{
public:
	void Run(); // �������� ����� ������ ���� ���, ����� �������� ���� ������� �� ����� ������ Stop()
	virtual ~SDLApplication(); // ����������

protected:
	void Stop(); // ���������� ������� ������
	virtual void ProcessEvents(); // ���������� ���� ������������
	virtual void ProcessEvent(SDL_Event Event) = 0;
	virtual void Main() = 0; // �������� ������
	virtual void Render() = 0; // ������� �� ����� ������� ��������
	void InitializeSDL(int ScreenWidth, int ScreenHeight, int ColorDepth, int SDLflags); // ���������������� ���������� SDL
	void LockSurface(SDL_Surface* surface);
	void UnlockSurface(SDL_Surface* surface);
	void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 R, Uint8 G, Uint8 B);
	SDL_Surface* Screen;
	long long frames;

private:
	bool Running;
};

#endif
