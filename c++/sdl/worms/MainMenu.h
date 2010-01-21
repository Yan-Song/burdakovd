#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>
#include <Sprite.h>
#include <UI/Element.h>
#include <UI/ElementSet.h>
#include <ISimpleGameLoop.h>
#include "Engine.h"

class SDLApplication;

class MainMenu : public UI::ElementSet
{
private:
	MainMenu(const MainMenu& );
	MainMenu& operator =(const MainMenu& );
	
	const SharedSprite background;

protected:
	Engine* app;

	class MenuItems;

public:
	MainMenu(Engine* const app, const SharedState resume = SharedState());

	virtual void ProcessEvent(const SDL_Event& ); // обработать событие, поступившее от пользователя

	virtual void Render(); // без комментариев
};

#endif
