#ifndef ISIMPLEGAMELOOP_H
#define ISIMPLEGAMELOOP_H

#include <SDL.h>

class ISimpleGameLoop
{
public:
	virtual void ProcessEvent(const SDL_Event&) = 0; // ���������� �������, ����������� �� ������������
	virtual void Main() = 0; // �������� ������
	virtual void Render() = 0; // ��� ������������
};

#endif
