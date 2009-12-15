#include <SDL.h>
#include <SDLApplication.h>
#include "Element.h"

int UI::Element::GetWidth() const
{
	return width;
}

int UI::Element::GetHeight() const
{
	return height;
}

int UI::Element::GetBottom() const
{
	return bottom;
}

int UI::Element::GetLeft() const
{
	return left;
}

void UI::Element::SetWidth(const int w)
{
	width = w;
	onLayoutChanged();
}

void UI::Element::SetHeight(const int h)
{
	height = h;
	onLayoutChanged();
}

void UI::Element::SetLeft(const int l)
{
	left = l;
	onLayoutChanged();
}

void UI::Element::SetBottom(const int b)
{
	bottom = b;
	onLayoutChanged();
}

void UI::Element::SetCenter(const ScreenPoint& center)
{
	SetLeft(center[0] - GetWidth() / 2);
	SetBottom(center[1] - GetHeight() / 2);
}

void UI::Element::Enable()
{
	enabled = true;
}

void UI::Element::Disable()
{
	enabled = false;
}

bool UI::Element::Enabled() const
{
	return enabled;
}

ScreenPoint UI::Element::GetCenter() const
{
	return ScreenPointByCoords(GetLeft() + GetWidth() / 2, GetBottom() + GetHeight() / 2);
}

void UI::Element::Clip()
{
	SDL_Rect rect;
	rect.x = static_cast<Sint16>(GetLeft());
	rect.y = static_cast<Sint16>(app->Screen->h - 1 - GetBottom() - GetHeight());
	rect.w = static_cast<Uint16>(GetWidth());
	rect.h = static_cast<Uint16>(GetHeight());

	SDL_SetClipRect(app->Screen, &rect);
}

void UI::Element::UnClip()
{
	SDL_SetClipRect(app->Screen, NULL);
}

void UI::Element::ProcessEvent(const SDL_Event& )
{

}

void UI::Element::Main()
{

}

void UI::Element::Render()
{

}

void UI::Element::onLayoutChanged()
{

}
