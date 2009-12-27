#include <SDL.h>
#include <SDLApplication.h>
#include <Utils.h>
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

void UI::Element::SetEnabled(const bool enabled_)
{
	enabled = enabled_;
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
	// сохранить предыдущий прямоугольник
	SDL_Rect prev;
	SDL_GetClipRect(app->Screen, &prev);
	clipStack.push(prev);

	// посчитать свой
	SDL_Rect me;
	me.x = static_cast<Sint16>(GetLeft());
	me.y = static_cast<Sint16>(app->Screen->h - 1 - GetBottom() - GetHeight());
	me.w = static_cast<Uint16>(GetWidth());
	me.h = static_cast<Uint16>(GetHeight());

	// пересечь с предыдущим
	SDL_Rect intersection = Intersect(prev, me);

	// обрезать по пересечению
	SDL_SetClipRect(app->Screen, &intersection);
}

void UI::Element::UnClip()
{
	// востановить предыдущий
	SDL_SetClipRect(app->Screen, &(clipStack.top()));
	clipStack.pop();
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

void UI::Element::Maximize()
{
	SetLeft(0);
	SetBottom(0);
	SetWidth(app->Screen->w);
	SetHeight(app->Screen->h);
}

ScreenPoint UI::Element::GetLeftBottom() const
{
	return ScreenPointByCoords(GetLeft(), GetBottom());
}
