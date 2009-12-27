#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <vector>
#include <ISimpleGameLoop.h>
#include <UI/Element.h>
#include <UI/ElementSet.h>
#include "Engine.h"

class SettingsDialog : public UI::ElementSet
{
private:
	Engine* app;

	SettingsDialog(const SettingsDialog& );
	SettingsDialog& operator =(const SettingsDialog& );

	class SettingsItem;
	typedef Shared::shared_ptr<SettingsItem> SharedSettingsItem;
	typedef std::vector<SharedSettingsItem> Settings;
	Settings settings;

public:
	SettingsDialog(Engine* const app);

	virtual void ProcessEvent(const SDL_Event& Event);

	virtual void Render();
};

#endif
