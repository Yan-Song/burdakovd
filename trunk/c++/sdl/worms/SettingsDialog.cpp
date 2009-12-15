#include <SDL.h>
#include <UI/Button.h>
#include "MainMenu.h"
#include "SettingsDialog.h"

namespace
{
	class OKButton : public UI::Button
	{
	private:
		OKButton(const OKButton& );
		OKButton& operator =(const OKButton& );

	public:
		OKButton(Engine* const app_) : UI::Button(app_, "OK")
		{
		}
	};

	class CancelButton : public UI::Button
	{
	private:
		Engine* app;

		CancelButton(const CancelButton& );
		CancelButton& operator =(const CancelButton& );

	public:
		CancelButton(Engine* const app_) : UI::Button(app_, "Cancel"), app(app_)
		{
		}

		virtual void onClick()
		{
			app->SetNextState(SharedState(new MainMenu(app)));
		}
	};
}

SettingsDialog::SettingsDialog(Engine* const app_) : app(app_)
{
	UI::SharedElement OK(new OKButton(app));
	UI::SharedElement Cancel(new CancelButton(app));

	OK->SetCenter(ScreenPointByCoords(app->Screen->w * 90 / 100, app->Screen->h * 5 / 100));
	Cancel->SetCenter(ScreenPointByCoords(app->Screen->w * 80 / 100, app->Screen->h * 5 / 100));

	Add(OK);
	Add(Cancel);
}

void SettingsDialog::ProcessEvent(const SDL_Event &Event)
{
	if(Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE)
	{
		app->SetNextState(SharedState(new MainMenu(app)));
	}

	ElementSet::ProcessEvent(Event);
}

void SettingsDialog::Render()
{
	app->ClearScreen(Color(0xe0e0e0));

	ElementSet::Render();
}
