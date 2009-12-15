#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>
#include <UI/Element.h>
#include <ISimpleGameLoop.h>

class SDLApplication;

class MainMenu : public ISimpleGameLoop
{
private:
	MainMenu(const MainMenu& );
	MainMenu& operator =(const MainMenu& );

protected:
	SDLApplication* app;

	class MenuItems;

	typedef std::vector<UI::SharedElement> ElementList;
	ElementList elements;

public:
	MainMenu(SDLApplication* const app);

	virtual void ProcessEvent(const SDL_Event& ); // обработать событие, поступившее от пользователя

	virtual void Main(); // основная логика

	virtual void Render(); // без комментариев
};

#endif
