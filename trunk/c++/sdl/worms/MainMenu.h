#ifndef MAINMENU_H
#define MAINMENU_H

#include <ISimpleGameLoop.h>

class MainMenu : public ISimpleGameLoop
{
public:
	virtual void ProcessEvent(const SDL_Event&); // ���������� �������, ����������� �� ������������
	virtual void Main(); // �������� ������
	virtual void Render(); // ��� ������������
};

#endif
