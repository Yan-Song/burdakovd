#include <sstream>
#include <string>
#include <SDL.h>
#include <UI/Button.h>
#include <UI/ColorSelector.h>
#include <UI/Label.h>
#include "Counter.h"
#include "MainMenu.h"
#include "Registrator.h"
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

class SettingsDialog::SettingsItem : public UI::ElementSet
{
public:
	size_t ID;
	UI::SharedLabel Name;
	UI::SharedColorSelector Color;
	UI::SharedCounter Count;

	SettingsItem(Engine* const app, const ScreenPoint& LeftBottom, const size_t ID_, const std::string& name) :
		UI::ElementSet(app), ID(ID_),
		Name(new UI::Label(app, name, GetFont("Fonts/arialbd.ttf", 16))),
		Color(new UI::ColorSelector(app)),
		Count(new UI::Counter(app, 0, 99, 0, Vector00))
	{
		UI::ElementSet::Add(Name);
		UI::ElementSet::Add(Color);
		UI::ElementSet::Add(Count);

		SetLeft(LeftBottom[0]);
		SetBottom(LeftBottom[1]);
		SetWidth(300);
		SetHeight(24);
	};

protected:
	virtual void onLayoutChanged()
	{
		const int nameWidth = 120;

		Name->SetLeft(GetLeft());
		Name->SetBottom(GetBottom());
		Name->SetHeight(GetHeight());

		Color->SetLeft(GetLeft() + nameWidth + 20);
		Color->SetBottom(GetBottom());
		Color->SetWidth(GetHeight());
		Color->SetHeight(GetHeight());
		
		Count->SetLeft(GetLeft() + nameWidth + 20 + Color->GetWidth() + 40);
		Count->SetBottom(GetBottom());
	}
};

SettingsDialog::SettingsDialog(Engine* const app_) : ElementSet(app_), app(app_), settings()
{
	Maximize();

	UI::SharedElement OK(new OKButton(app));
	UI::SharedElement Cancel(new CancelButton(app));

	OK->SetCenter(ScreenPointByCoords(app->Screen->w * 90 / 100, app->Screen->h * 5 / 100));
	Cancel->SetCenter(ScreenPointByCoords(app->Screen->w * 80 / 100, app->Screen->h * 5 / 100));

	Add(OK);
	Add(Cancel);

	Registrator registrator;
	settings.reserve(registrator.Count());

	for(size_t i = 0; i < registrator.Count(); ++i)
	{
		ScreenPoint lb = ScreenPointByCoords(50, app->Screen->h - static_cast<int>(i) * 36 - 60);

		std::ostringstream os;
		os << (i + 1) << ") " << registrator.ClassName(i);

		SharedSettingsItem item(new SettingsItem(app, lb, i, os.str()));

		settings.push_back(item);
		UI::ElementSet::Add(item);
	}
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