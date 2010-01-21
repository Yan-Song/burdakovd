#include <Color.h>
#include <SDLApplication.h>
#include <Sprite.h>
#include <UI/Clickable.h>
#include "Battle.h"
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
		Quit(Engine* const app) : MenuItem(app, "Sprites/UI/Button/Quit")
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
		New(Engine* const app) : MenuItem(app, "Sprites/UI/Button/New")
		{

		}

		virtual void onClick()
		{
			app->SetNextState(SharedState(new SettingsDialog(app)));
		}
	};

	class Resume : public UI::MenuItem
	{
	private:
		Resume& operator =(const Resume& );

	private:
		const SharedState resume;

	public:
		Resume(Engine* const app, const SharedState& resume_) : MenuItem(app, "Sprites/UI/Button/Resume"), resume(resume_)
		{
			SetEnabled(static_cast<bool>(resume));
		}

		virtual void onClick()
		{
			dynamic_cast<Battle*>(resume.get()) -> Resume();
			app->SetNextState(resume);
		}
	};
};

MainMenu::MainMenu(Engine* const app_, const SharedState resume) : UI::ElementSet(app_), background(new Sprite("Sprites/UI/MainMenu/background.png")), app(app_)
{
	Maximize();

	Add(UI::SharedElement(new MenuItems::New(app)));
	Add(UI::SharedElement(new MenuItems::Resume(app, resume)));
	Add(UI::SharedElement(new MenuItems::Quit(app)));

	const int distance = 10;
	int totalWidth = (elements.size() - 1) * distance;
	for(Elements::const_iterator it = elements.begin(); it != elements.end(); ++it)
	{
		totalWidth += (*it)->GetWidth();
	}

	const int baseX = (GetWidth() - totalWidth) / 2;
	int offsetX = baseX;
	const int centerY = GetHeight() * 2 / 3;

	for(Elements::const_iterator it = elements.begin(); it != elements.end(); offsetX += distance + (*it)->GetWidth(), ++it)
	{
		(*it)->SetCenter(ScreenPointByCoords(offsetX + (*it)->GetWidth() / 2, centerY));
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
	background->Draw(app, GetCenter());

	ElementSet::Render();
}
