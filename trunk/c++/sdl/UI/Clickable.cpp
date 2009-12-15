#include <iostream>
#include "Clickable.h"

UI::Clickable::Clickable(SDLApplication* const app) : MouseOverable(app), halfClicked(false)
{
	
}

void UI::Clickable::onMouseDown()
{
	
}

void UI::Clickable::onMouseUp()
{
	
}

void UI::Clickable::onClick()
{
	
}

bool UI::Clickable::isElementPressed() const
{
	return halfClicked && isMouseOver();
}

void UI::Clickable::ProcessEvent(const SDL_Event& Event)
{
	if(Event.type == SDL_MOUSEBUTTONDOWN && Event.button.button == SDL_BUTTON_LEFT && isInside(Event.button))
	{
		onMouseDown();
		halfClicked = true;
	}
	else if(Event.type == SDL_MOUSEBUTTONUP && Event.button.button == SDL_BUTTON_LEFT)
	{
		if(isInside(Event.button) && halfClicked)
		{
			onClick();
			onMouseUp();
		}

		halfClicked = false;
	}
}
