#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <SDL.h>

class SDLApplication
{
public:
	SDLApplication(); // �����������
	void Run(); // �������� ����� ������ ���� ���, ����� �������� ���� ������� �� ����� ������ Stop()
	virtual ~SDLApplication(); // ����������

protected:
	void Stop(); // ���������� ������� ������
	virtual void ProcessEvents(); // ���������� ���� ������������
	virtual void Main(); // �������� ������
	virtual void Render(); // ������� �� ����� ������� ��������
	void InitializeSDL(int ScreenWidth, int ScreenHeight, int ColorDepth); // ���������������� ���������� SDL

private:
	bool Running;
	SDL_Surface* Screen;
};

#endif
