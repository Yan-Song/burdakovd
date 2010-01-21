#include "Engine.h"
#include "MenuItem.h"

const std::string UI::MenuItem::MenuFont = "Fonts/Luismimurder.ttf";

UI::MenuItem::MenuItem(Engine* const app_, const std::string& text_)
: Clickable(app_), text(text_), normal(), hovered(), disabled(), app(app_)
{
	updateSprites();
}

void UI::MenuItem::Render()
{
	Clip();

	if(Enabled())
	{
		if(isMouseOver())
		{
			hovered->Draw(app, GetCenter());
		}
		else
		{
			normal->Draw(app, GetCenter());
		}
	}
	else
	{
		disabled->Draw(app, GetCenter());
	}

	UnClip();
}

void UI::MenuItem::onLayoutChanged()
{
	updateSprites();
}

void UI::MenuItem::updateSprites()
{
	normal = SharedSprite(new Sprite(GetFont(MenuFont, 48), text, Palette::Black));
	hovered = SharedSprite(new Sprite(GetFont(MenuFont, 54), text, Palette::Green));
	disabled = SharedSprite(new Sprite(GetFont(MenuFont, 48), text, Color(0xd0d0d0)));
}
