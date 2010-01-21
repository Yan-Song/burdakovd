#include <sstream>
#include <string>
#include <SDL.h>
#include <UI/Button.h>
#include <UI/ColorSelector.h>
#include <UI/Label.h>
#include "Battle.h"
#include "Counter.h"
#include "Engine.h"
#include "MainMenu.h"
#include "Registrator.h"
#include "SettingsDialog.h"

class SettingsDialog::Util
{
public:
	class OKButton : public UI::Button
	{
	private:
		Engine* const app;
		SettingsDialog* const parent;

	private:
		OKButton(const OKButton& );
		OKButton& operator =(const OKButton& );

	public:
		OKButton(Engine* const app_, SettingsDialog* const parent_) : UI::Button(app_, "OK"), app(app_), parent(parent_)
		{
			SetButtonDefault(true);
		}

	protected:
		virtual void onClick()
		{
			app->SetNextState(SharedState(new Battle(app, parent->GetTeams())));
		}
	};

	class CancelButton : public UI::Button
	{
	private:
		Engine* const app;

	private:
		CancelButton(const CancelButton& );
		CancelButton& operator =(const CancelButton& );

	public:
		CancelButton(Engine* const app_) : UI::Button(app_, "Cancel"), app(app_)
		{
			SetButtonCancel(true);
		}

	protected:
		virtual void onClick()
		{
			app->SetNextState(SharedState(new MainMenu(app)));
		}
	};
};

class SettingsDialog::SettingsItem : public UI::ElementSet
{
private:
	size_t ID;
	UI::SharedLabel Name;
	UI::SharedColorSelector Color;
	UI::SharedCounter Count;

public:
	SettingsItem(Engine* const app, const ScreenPoint& LeftBottom, const size_t ID_, const std::string& name) :
		UI::ElementSet(app), ID(ID_),
		Name(new UI::Label(app, name, GetFont("Fonts/Luismimurder.ttf", 32))),
		Color(new UI::ColorSelector(app)),
		Count(new UI::Counter(app, 0, 99, 0, Vector00))
	{
		UI::ElementSet::Add(Name);
		UI::ElementSet::Add(Color);
		UI::ElementSet::Add(Count);

		SetLeft(LeftBottom[0]);
		SetBottom(LeftBottom[1]);
		SetWidth(300);
		SetHeight(32);
	};

	bool HasTeam() const
	{
		return Count->GetValue() > 0;
	}

	Team GetTeam() const
	{
		return Team(ID, Color->color, Count->GetValue());
	}

protected:
	virtual void onLayoutChanged()
	{
		const int nameWidth = 150;

		Name->SetLeft(GetLeft());
		Name->SetBottom(GetBottom());
		Name->SetHeight(GetHeight());

		Color->SetLeft(GetLeft() + nameWidth + 20);
		Color->SetBottom(GetBottom());
		Color->SetWidth(GetHeight());
		Color->SetHeight(GetHeight());
		
		Count->SetLeft(GetLeft() + nameWidth  + Color->GetWidth() + 40);
		Count->SetBottom(GetBottom());
	}
};

SettingsDialog::SettingsDialog(Engine* const app_) : ElementSet(app_), background(new Sprite("Sprites/UI/SettingsDialog/background.png")), app(app_), settings()
{
	Maximize();

	UI::SharedElement OK(new Util::OKButton(app, this));
	UI::SharedElement Cancel(new Util::CancelButton(app));

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
	ElementSet::ProcessEvent(Event);
}

void SettingsDialog::Render()
{
	background->Draw(app, GetCenter());

	ElementSet::Render();
}

Teams SettingsDialog::GetTeams() const
{
	Teams teams;
	
	for(Settings::const_iterator it = settings.begin(); it != settings.end(); ++it)
		if((*it)->HasTeam())
			teams.push_back((*it)->GetTeam());

	return teams;
}
