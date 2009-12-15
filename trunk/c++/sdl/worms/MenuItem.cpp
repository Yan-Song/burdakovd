#include "MenuItem.h"

const std::string UI::MenuItem::MenuFont = "Fonts/arialbd.ttf";

UI::MenuItem::MenuItem(SDLApplication* const app, const std::string& text_) : Clickable(app), text(text_), normal(), hovered(), disabled()
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
	normal = SharedSprite(new Sprite(GetFont(MenuFont, 24), text, Palette::Black));
	hovered = SharedSprite(new Sprite(GetFont(MenuFont, 32), text, Palette::Blue));
	disabled = SharedSprite(new Sprite(GetFont(MenuFont, 24), text, Palette::Gray));
}
