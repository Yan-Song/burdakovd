#ifndef MAINMENU_H
#define MAINMENU_H

#include <ISimpleGameLoop.h>
#include <Shared.h>

class SDLApplication;

namespace UI
{
	class Element;
}

class MainMenu : public ISimpleGameLoop
{
private:
	Shared::shared_ptr<UI::Element> element;

public:
	MainMenu(SDLApplication* const app);

	virtual void ProcessEvent(const SDL_Event& ); // обработать событие, поступившее от пользователя
	
	virtual void Main(); // основная логика
	
	virtual void Render(); // без комментариев
};

#endif
