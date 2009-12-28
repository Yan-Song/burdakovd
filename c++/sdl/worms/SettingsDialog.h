#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <vector>
#include <UI/ElementSet.h>
#include "BattleSettings.h"

class Engine;

class SettingsDialog : public UI::ElementSet
{
private:
	SettingsDialog(const SettingsDialog& );
	SettingsDialog& operator =(const SettingsDialog& );

private:
	Engine* app;

	class Util;

	class SettingsItem;
	typedef Shared::shared_ptr<SettingsItem> SharedSettingsItem;
	typedef std::vector<SharedSettingsItem> Settings;
	Settings settings;

public:
	SettingsDialog(Engine* const app);

	virtual void ProcessEvent(const SDL_Event& Event);

	virtual void Render();

	Teams GetTeams() const;
};

#endif
