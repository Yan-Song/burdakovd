#include <iostream>
#include <SDLApplication.h>
#include <Vector.h>
#include "MouseOverable.h"


UI::MouseOverable::MouseOverable(SDLApplication* const app_) : Element(app_)
{

}

bool UI::MouseOverable::inside(const ScreenPoint& mouse) const
{
	return mouse[0] >= GetLeft()
		&& mouse[1] >= GetBottom()
		&& mouse[0] < GetLeft() + GetWidth()
		&& mouse[1] < GetBottom() + GetHeight();
}

bool UI::MouseOverable::isMouseOver() const
{
	const ScreenPoint mouse = app->GetMousePosition();

	return inside(mouse);
}

bool UI::MouseOverable::isInside(const SDL_MouseButtonEvent &Event) const
{
	const ScreenPoint mouse = ScreenPointByCoords(Event.x, app->Screen->h - 1 - Event.y);

	return inside(mouse);
}
