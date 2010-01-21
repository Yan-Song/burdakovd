#include "Engine.h"
#include "MenuItem.h"

UI::MenuItem::MenuItem(Engine* const app_, const std::string& path_)
: Clickable(app_), path(path_), normal(), hovered(), disabled(), app(app_)
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

void UI::MenuItem::updateSprites()
{
	normal = SharedSprite(new Sprite(path + "/" + "normal.png"));
	hovered = SharedSprite(new Sprite(path + "/" + "active.png"));
	disabled = SharedSprite(new Sprite(path + "/" + "disabled.png"));
	
	SetWidth(normal->GetWidth());
	SetHeight(normal->GetHeight());
}
