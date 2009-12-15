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
	class WormSetting;
	Engine* app;

	SettingsDialog(const SettingsDialog& );
	SettingsDialog& operator =(const SettingsDialog& );

public:
	SettingsDialog(Engine* const app);

	virtual void ProcessEvent(const SDL_Event& Event);

	virtual void Render();
};

#endif
