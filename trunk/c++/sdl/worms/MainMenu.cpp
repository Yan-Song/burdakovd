#include <Color.h>
#include <SDLApplication.h>
#include <Sprite.h>
#include <UI/Clickable.h>
#include "Engine.h"
#include "MainMenu.h"
#include "MenuItem.h"
#include "SettingsDialog.h"

class MainMenu::MenuItems
{
public:
	class Quit : public UI::MenuItem
	{
	public:
		Quit(Engine* const app) : MenuItem(app, "Quit")
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
		New(Engine* const app) : MenuItem(app, "New")
		{

		}

		virtual void onClick()
		{
			app->SetNextState(SharedState(new SettingsDialog(app)));
		}
	};
};

MainMenu::MainMenu(Engine* const app_) : UI::ElementSet(app_), app(app_)
{
	Maximize();

	Add(UI::SharedElement(new MenuItems::New(app)));
	Add(UI::SharedElement(new MenuItems::Quit(app)));

	// разместить элементы на экране
	const int ItemWidth = 200;
	const int ItemHeight = 50;
	const int ItemLeft = (app->Screen->w - ItemWidth) / 2;
	const int MenuBottom = (app->Screen->h - ItemHeight * static_cast<int>(elements.size())) / 2;
	
	size_t i = elements.size() - 1;
	for(Elements::const_iterator it = elements.begin(); it != elements.end(); ++it, --i)
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
	
	ElementSet::ProcessEvent(Event);
}

void MainMenu::Render()
{
	app->ClearScreen(Color(0xe0e0e0));

	ElementSet::Render();
}
