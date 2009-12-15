#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>
#include <UI/Element.h>
#include <ISimpleGameLoop.h>

class SDLApplication;

class MainMenu : public ISimpleGameLoop
{
protected:
	SDLApplication* app;

	class MenuItems;

	typedef std::vector<UI::SharedElement> ElementList;
	ElementList elements;

public:
	MainMenu(SDLApplication* const app);

	virtual void ProcessEvent(const SDL_Event& ); // ���������� �������, ����������� �� ������������
	
	virtual void Main(); // �������� ������
	
	virtual void Render(); // ��� ������������
};

#endif
