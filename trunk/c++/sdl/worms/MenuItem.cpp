#include "Engine.h"
#include "MenuItem.h"

const std::string UI::MenuItem::MenuFont = "Fonts/arialbd.ttf";

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
	normal = SharedSprite(new Sprite(GetFont(MenuFont, 36), text, Palette::Black));
	hovered = SharedSprite(new Sprite(GetFont(MenuFont, 48), text, Palette::Blue));
	disabled = SharedSprite(new Sprite(GetFont(MenuFont, 36), text, Palette::Gray));
}
