#include <iostream>
#include <SDLApplication.h>
#include <Vector.h>
#include "MouseOverable.h"


UI::MouseOverable::MouseOverable(SDLApplication* const app_) : app(app_) {}

bool UI::MouseOverable::isMouseOver() const
{
	const ScreenPoint mouse = app->GetMousePosition();

	const bool inside =
		mouse[0] >= GetLeft()
		&& mouse[1] >= GetBottom()
		&& mouse[0] < GetLeft() + GetWidth()
		&& mouse[1] < GetBottom() + GetHeight();

	return inside;
}
