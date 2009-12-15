#include <Color.h>
#include <SDLApplication.h>
#include <Sprite.h>
#include <UI/Clickable.h>
#include "MainMenu.h"
#include "MenuItem.h"

class MainMenu::MenuItems
{
public:
	class Quit : public UI::MenuItem
	{
	public:
		Quit(SDLApplication* const app) : MenuItem(app, "Quit")
		{
		}

		virtual void onClick()
		{
			app->Stop();
		}
	};

	class New : public UI::MenuItem
	{
	public:

	};
};

MainMenu::MainMenu(SDLApplication* const app_) : app(app_), elements()
{
	elements.push_back(UI::SharedElement(new MenuItems::Quit(app)));

	// разместить элементы на экране
	const int ItemWidth = 200;
	const int ItemHeight = 60;
	const int ItemLeft = (app->Screen->w - ItemWidth) / 2;
	const int MenuBottom = (app->Screen->h - ItemHeight * static_cast<int>(elements.size())) / 2;
	
	size_t i = elements.size() - 1;
	for(ElementList::const_iterator it = elements.begin(); it != elements.end(); ++it, --i)
	{
		(*it)->SetWidth(ItemWidth);
		(*it)->SetHeight(ItemHeight);
		(*it)->SetLeft(ItemLeft);
		(*it)->SetBottom(MenuBottom + static_cast<int>(i) * ItemHeight);
	}
}

void MainMenu::ProcessEvent(const SDL_Event& Event)
{
	if(Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE)
		app->Stop();

	for(ElementList::const_iterator it = elements.begin(); it != elements.end(); ++it)
		(*it)->ProcessEvent(Event);
}

void MainMenu::Main()
{
	for(ElementList::const_iterator it = elements.begin(); it != elements.end(); ++it)
		(*it)->Main();
}

void MainMenu::Render()
{
	app->ClearScreen(Color(0xe0e0e0));
	for(ElementList::const_iterator it = elements.begin(); it != elements.end(); ++it)
		(*it)->Render();
}
